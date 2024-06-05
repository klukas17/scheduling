//
// Created by mihael on 5/21/24.
//

#include "TreeBasedGeneticProgrammingSerializationOperator.h"

#include "TreeBasedGeneticProgramming.h"

#include "TBGPNodeBranch.h"
#include "TBGPNodeConst.h"
#include "TBGPNodeDivide.h"
#include "TBGPNodeMinus.h"
#include "TBGPNodeParam.h"
#include "TBGPNodePlus.h"
#include "TBGPNodeRoot.h"
#include "TBGPNodeSquare.h"
#include "TBGPNodeTimes.h"

#include "sstream"
#include "TBGPNodeDepthAdjuster.h"
#include "TBGPNodeUnaryMinus.h"

TreeBasedGeneticProgrammingSerializationOperator::TreeBasedGeneticProgrammingSerializationOperator(TreeBasedGeneticProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
}

TreeBasedGeneticProgrammingSerializationOperator::~TreeBasedGeneticProgrammingSerializationOperator() = default;

std::vector<std::string> TreeBasedGeneticProgrammingSerializationOperator::serialize(Genotype* genotype) {
    auto tbgp = dynamic_cast<TreeBasedGeneticProgramming*>(genotype);
    std::ostringstream oss;
    for (auto input : tbgp->getInputs()) {
        oss << input << " ";
    }
    auto body = serializeNode(tbgp->getRootNode(), 0);
    std::vector<std::string> result = {oss.str()};
    for (auto line : body) {
        result.push_back(line);
    }
    return result;
}

std::vector<std::string> TreeBasedGeneticProgrammingSerializationOperator::serializeNode(TBGPNode* node, int depth) {

    std::ostringstream oss;

    for (int i = 0; i < depth; i++) {
        oss << " ";
    }

    std::vector<std::string> children_node_lines;

    switch (node->node_type)
    {

    case TBGP_ABSTRACT:
        {
            break;
        }

    case TBGP_CONST:
        {
            auto const_node = dynamic_cast<TBGPNodeConst*>(node);
            oss << "CONST " << const_node->constant;
            break;
        }

    case TBGP_PARAM:
        {
            auto param_node = dynamic_cast<TBGPNodeParam*>(node);
            oss << "PARAM " << param_node->param;
            break;
        }

    case TBGP_UNARY_MINUS:
        {
            auto unary_minus_node = dynamic_cast<TBGPNodeUnaryMinus*>(node);
            oss << "UNARY_MINUS";
            for (const auto& line : serializeNode(unary_minus_node->operand_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            break;
        }

    case TBGP_PLUS:
        {
            auto plus_node = dynamic_cast<TBGPNodePlus*>(node);
            oss << "PLUS";
            for (const auto& line : serializeNode(plus_node->first_summand_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            for (const auto& line : serializeNode(plus_node->second_summand_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            break;
        }

    case TBGP_MINUS:
        {
            auto minus_node = dynamic_cast<TBGPNodeMinus*>(node);
            oss << "MINUS";
            for (const auto& line : serializeNode(minus_node->minuend_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            for (const auto& line : serializeNode(minus_node->subtrahend_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            break;
        }

    case TBGP_TIMES:
        {
            auto times_node = dynamic_cast<TBGPNodeTimes*>(node);
            oss << "TIMES";
            for (const auto& line : serializeNode(times_node->first_factor_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            for (const auto& line : serializeNode(times_node->second_factor_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            break;
        }

    case TBGP_DIVIDE:
        {
            auto divide_node = dynamic_cast<TBGPNodeDivide*>(node);
            oss << "DIVIDE";
            for (const auto& line : serializeNode(divide_node->dividend_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            for (const auto& line : serializeNode(divide_node->divisor_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            break;
        }

    case TBGP_SQUARE:
        {
            auto square_node = dynamic_cast<TBGPNodeSquare*>(node);
            oss << "SQUARE";
            for (const auto& line : serializeNode(square_node->base_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            break;
        }

    case TBGP_ROOT:
        {
            auto root_node = dynamic_cast<TBGPNodeRoot*>(node);
            oss << "ROOT";
            for (const auto& line : serializeNode(root_node->radicand_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            break;
        }

    case TBGP_BRANCH:
        {
            auto branch_node = dynamic_cast<TBGPNodeBranch*>(node);
            oss << "BRANCH";
            for (const auto& line : serializeNode(branch_node->if_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            for (const auto& line : serializeNode(branch_node->then_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            for (const auto& line : serializeNode(branch_node->else_node, depth + 1)) {
                children_node_lines.push_back(line);
            }
            break;
        }

    }

    std::vector<std::string> result = {oss.str()};
    for (const auto& line : children_node_lines) {
        result.push_back(line);
    }

    return result;
}


Genotype* TreeBasedGeneticProgrammingSerializationOperator::deserialize(std::vector<std::string> representation) {

    std::istringstream iss(representation[0]);
    std::vector<std::string> inputs;
    std::string input;
    while (iss >> input) {
        inputs.push_back(input);
    }

    int index = 1;
    auto tbgp = new TreeBasedGeneticProgramming(deserializeNode(representation, index));
    tbgp->setInputs(inputs);

    TBGPNodeDepthAdjuster::adjustDepths(tbgp, blueprint->max_height);

    return tbgp;
}

TBGPNode* TreeBasedGeneticProgrammingSerializationOperator::deserializeNode(std::vector<std::string>& representation, int& index) {
    int spaces = 0;
    auto line = representation[index];
    index++;

    while (line[spaces] == ' ') {
        spaces++;
    }

    auto line_stripped = line.substr(spaces);
    std::istringstream iss(line_stripped);
    std::string node_type;
    iss >> node_type;

    if (node_type == "CONST") {
        double c;
        iss >> c;
        auto node = new TBGPNodeConst();
        node->constant = c;
        return node;
    }

    else if (node_type == "PARAM") {
        std::string p;
        iss >> p;
        auto node = new TBGPNodeParam();
        node->param = p;
        return node;
    }

    else if (node_type == "UNARY_MINUS") {
        auto node = new TBGPNodeUnaryMinus();
        node->operand_node = deserializeNode(representation, index);
        node->operand_node->parent = node;
        return node;
    }

    else if (node_type == "PLUS") {
        auto node = new TBGPNodePlus();
        node->first_summand_node = deserializeNode(representation, index);
        node->second_summand_node = deserializeNode(representation, index);
        node->first_summand_node->parent = node;
        node->second_summand_node->parent = node;
        return node;
    }

    else if (node_type == "MINUS") {
        auto node = new TBGPNodeMinus();
        node->minuend_node = deserializeNode(representation, index);
        node->subtrahend_node = deserializeNode(representation, index);
        node->minuend_node->parent = node;
        node->subtrahend_node->parent = node;
        return node;
    }

    else if (node_type == "TIMES") {
        auto node = new TBGPNodeTimes();
        node->first_factor_node = deserializeNode(representation, index);
        node->second_factor_node = deserializeNode(representation, index);
        node->first_factor_node->parent = node;
        node->second_factor_node->parent = node;
        return node;
    }

    else if (node_type == "DIVIDE") {
        auto node = new TBGPNodeDivide();
        node->dividend_node = deserializeNode(representation, index);
        node->divisor_node = deserializeNode(representation, index);
        node->dividend_node->parent = node;
        node->divisor_node->parent = node;
        return node;
    }

    else if (node_type == "SQUARE") {
        auto node = new TBGPNodeSquare();
        node->base_node = deserializeNode(representation, index);
        node->base_node->parent = node;
        return node;
    }

    else if (node_type == "ROOT") {
        auto node = new TBGPNodeRoot();
        node->radicand_node = deserializeNode(representation, index);
        node->radicand_node->parent = node;
        return node;
    }

    else if (node_type == "BRANCH") {
        auto node = new TBGPNodeBranch();
        node->if_node = deserializeNode(representation, index);
        node->then_node = deserializeNode(representation, index);
        node->else_node = deserializeNode(representation, index);
        node->if_node->parent = node;
        node->then_node->parent = node;
        node->else_node->parent = node;
        return node;
    }
}
