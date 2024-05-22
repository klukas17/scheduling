//
// Created by mihael on 5/21/24.
//

#include "TBGPNodeFactory.h"

#include <climits>
#include <utility>

#include "TBGPNodeBranch.h"
#include "TBGPNodeConst.h"
#include "TBGPNodeDivide.h"
#include "TBGPNodeMinus.h"
#include "TBGPNodeParam.h"
#include "TBGPNodePlus.h"
#include "TBGPNodeRoot.h"
#include "TBGPNodeSquare.h"
#include "TBGPNodeTimes.h"
#include "TBGPNodeUnaryMinus.h"
#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

std::vector<TBGPNodeType> TBGPNodeFactory::inner_node_types = {
    UNARY_MINUS,
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    SQUARE,
    ROOT,
    BRANCH
};

TBGPNodeFactory::TBGPNodeFactory(double leaf_const_chance, double leaf_param_chance, double constant_min, double constant_max) {
    this->leaf_const_chance = leaf_const_chance;
    this->leaf_param_chance = leaf_param_chance;
    this->chance_generator = new UniformRealDistributionGenerator(0, 1);
    this->constant_generator = new UniformRealDistributionGenerator(constant_min, constant_max);
    this->index_generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

void TBGPNodeFactory::setInputs(std::vector<std::string> inputs) {
    this->inputs = std::move(inputs);
}

TBGPNode* TBGPNodeFactory::createNode(int max_height) {

    auto const_chance = leaf_const_chance;
    auto param_chance = leaf_param_chance;

    if (max_height == 1) {
        const_chance = leaf_const_chance / (leaf_const_chance + leaf_param_chance);
        param_chance = 1 - const_chance;
    }

    auto chance = chance_generator->generate();

    if (chance < const_chance) {
        auto node = new TBGPNodeConst();
        node->constant = constant_generator->generate();
        return node;
    }

    else if (chance < const_chance + param_chance) {
        auto node = new TBGPNodeParam();
        auto param_index = index_generator->generate() % inputs.size();
        node->param = inputs[param_index];
        return node;
    }

    else {
        auto node_index = index_generator->generate() % inner_node_types.size();
        auto node_type = inner_node_types[node_index];

        switch(node_type)
        {

        case UNARY_MINUS:
            {
                auto node = new TBGPNodeUnaryMinus();
                node->operand_node = createNode(max_height - 1);
                node->operand_node->parent = node;
                return node;
            }

        case PLUS:
            {
                auto node = new TBGPNodePlus();
                node->first_summand_node = createNode(max_height - 1);
                node->second_summand_node = createNode(max_height - 1);
                node->first_summand_node->parent = node;
                node->second_summand_node->parent = node;
                return node;
            }

        case MINUS:
            {
                auto node = new TBGPNodeMinus();
                node->minuend_node = createNode(max_height - 1);
                node->subtrahend_node = createNode(max_height - 1);
                node->minuend_node->parent = node;
                node->subtrahend_node->parent = node;
                return node;
            }

        case TIMES:
            {
                auto node = new TBGPNodeTimes();
                node->first_factor_node = createNode(max_height - 1);
                node->second_factor_node = createNode(max_height - 1);
                node->first_factor_node->parent = node;
                node->second_factor_node->parent = node;
                return node;
            }

        case DIVIDE:
            {
                auto node = new TBGPNodeDivide();
                node->dividend_node = createNode(max_height - 1);
                node->divisor_node = createNode(max_height - 1);
                node->dividend_node->parent = node;
                node->divisor_node->parent = node;
                return node;
            }

        case SQUARE:
            {
                auto node = new TBGPNodeSquare();
                node->base_node = createNode(max_height - 1);
                node->base_node->parent = node;
                return node;
            }

        case ROOT:
            {
                auto node = new TBGPNodeRoot();
                node->radicand_node = createNode(max_height - 1);
                node->radicand_node->parent = node;
                return node;
            }

        case BRANCH:
            {
                auto node = new TBGPNodeBranch();
                node->if_node = createNode(max_height - 1);
                node->then_node = createNode(max_height - 1);
                node->else_node = createNode(max_height - 1);
                node->if_node->parent = node;
                node->then_node->parent = node;
                node->else_node->parent = node;
                return node;
            }
        }
    }

}
