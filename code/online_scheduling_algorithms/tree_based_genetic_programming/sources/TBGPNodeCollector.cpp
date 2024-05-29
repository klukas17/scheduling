//
// Created by mihael on 5/21/24.
//

#include "TBGPNodeCollector.h"

#include "TBGPNodeBranch.h"
#include "TBGPNodeDivide.h"
#include "TBGPNodeMinus.h"
#include "TBGPNodePlus.h"
#include "TBGPNodeRoot.h"
#include "TBGPNodeSquare.h"
#include "TBGPNodeTimes.h"
#include "TBGPNodeUnaryMinus.h"

std::vector<TBGPNode*> TBGPNodeCollector::collect(TreeBasedGeneticProgramming* tbgp, int max_height) {
    std::vector<TBGPNode*> collection;
    traverseTree(tbgp->getRootNode(), max_height, collection);
    return collection;
}

void TBGPNodeCollector::traverseTree(TBGPNode* node, int max_height, std::vector<TBGPNode*>& collection) {
    if (node->height <= max_height) {
        collection.push_back(node);
    }

    switch (node->node_type)
    {

    case TBGP_ABSTRACT:
    case TBGP_CONST:
    case TBGP_PARAM:
        {
            break;
        }

    case TBGP_UNARY_MINUS:
        {
            auto unary_minus_node = dynamic_cast<TBGPNodeUnaryMinus*>(node);
            traverseTree(unary_minus_node->operand_node, max_height, collection);
            break;
        }

    case TBGP_PLUS:
        {
            auto plus_node = dynamic_cast<TBGPNodePlus*>(node);
            traverseTree(plus_node->first_summand_node, max_height, collection);
            traverseTree(plus_node->second_summand_node, max_height, collection);
            break;
        }

    case TBGP_MINUS:
        {
            auto minus_node = dynamic_cast<TBGPNodeMinus*>(node);
            traverseTree(minus_node->minuend_node, max_height, collection);
            traverseTree(minus_node->subtrahend_node, max_height, collection);
            break;
        }

    case TBGP_TIMES:
        {
            auto times_node = dynamic_cast<TBGPNodeTimes*>(node);
            traverseTree(times_node->first_factor_node, max_height, collection);
            traverseTree(times_node->second_factor_node, max_height, collection);
            break;
        }

    case TBGP_DIVIDE:
        {
            auto divide_node = dynamic_cast<TBGPNodeDivide*>(node);
            traverseTree(divide_node->dividend_node, max_height, collection);
            traverseTree(divide_node->divisor_node, max_height, collection);
            break;
        }

    case TBGP_SQUARE:
        {
            auto square_node = dynamic_cast<TBGPNodeSquare*>(node);
            traverseTree(square_node->base_node, max_height, collection);
            break;
        }

    case TBGP_ROOT:
        {
            auto root_node = dynamic_cast<TBGPNodeRoot*>(node);
            traverseTree(root_node->radicand_node, max_height, collection);
            break;
        }

    case TBGP_BRANCH:
        {
            auto branch_node = dynamic_cast<TBGPNodeBranch*>(node);
            traverseTree(branch_node->if_node, max_height, collection);
            traverseTree(branch_node->then_node, max_height, collection);
            traverseTree(branch_node->else_node, max_height, collection);
            break;
        }

    }
}
