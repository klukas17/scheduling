//
// Created by mihael on 5/21/24.
//

#include "TBGPNodeDepthAdjuster.h"
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

void TBGPNodeDepthAdjuster::adjustDepths(TreeBasedGeneticProgramming* tbgp, int max_depth) {
    adjustHeightForNode(tbgp->getRootNode());
    adjustMaxDepthForNode(tbgp->getRootNode(), max_depth);
}

void TBGPNodeDepthAdjuster::adjustHeightForNode(TBGPNode* node) {

    switch (node->node_type)
    {

    case ABSTRACT:
        {
            return;
        }
    case CONST:
        {
            auto const_node = dynamic_cast<TBGPNodeConst*>(node);
            const_node->height = 1;
            return;
        }

    case PARAM:
        {
            auto param_node = dynamic_cast<TBGPNodeParam*>(node);
            param_node->height = 1;
            return;
        }

    case UNARY_MINUS:
        {
            auto unary_minus_node = dynamic_cast<TBGPNodeUnaryMinus*>(node);
            adjustHeightForNode(unary_minus_node->operand_node);
            unary_minus_node->height = 1 + unary_minus_node->operand_node->height;
            return;
        }

    case PLUS:
        {
            auto plus_node = dynamic_cast<TBGPNodePlus*>(node);
            adjustHeightForNode(plus_node->first_summand_node);
            adjustHeightForNode(plus_node->second_summand_node);
            plus_node->height = 1 + std::max(
                plus_node->first_summand_node->height,
                plus_node->second_summand_node->height
            );
            return;
        }

    case MINUS:
        {
            auto minus_node = dynamic_cast<TBGPNodeMinus*>(node);
            adjustHeightForNode(minus_node->minuend_node);
            adjustHeightForNode(minus_node->subtrahend_node);
            minus_node->height = 1 + std::max(
                minus_node->minuend_node->height,
                minus_node->subtrahend_node->height
            );
            return;
        }

    case TIMES:
        {
            auto times_node = dynamic_cast<TBGPNodeTimes*>(node);
            adjustHeightForNode(times_node->first_factor_node);
            adjustHeightForNode(times_node->second_factor_node);
            times_node->height = 1 + std::max(
                times_node->first_factor_node->height,
                times_node->second_factor_node->height
            );
            return;
        }

    case DIVIDE:
        {
            auto divide_node = dynamic_cast<TBGPNodeDivide*>(node);
            adjustHeightForNode(divide_node->dividend_node);
            adjustHeightForNode(divide_node->divisor_node);
            divide_node->height = 1 + std::max(
                divide_node->dividend_node->height,
                divide_node->divisor_node->height
            );
            return;
        }

    case SQUARE:
        {
            auto square_node = dynamic_cast<TBGPNodeSquare*>(node);
            adjustHeightForNode(square_node->base_node);
            square_node->height = 1 + square_node->base_node->height;
            return;
        }

    case ROOT:
        {
            auto root_node = dynamic_cast<TBGPNodeRoot*>(node);
            adjustHeightForNode(root_node->radicand_node);
            root_node->height = 1 + root_node->radicand_node->height;
            return;
        }

    case BRANCH:
        {
            auto branch_node = dynamic_cast<TBGPNodeBranch*>(node);
            adjustHeightForNode(branch_node->if_node);
            adjustHeightForNode(branch_node->then_node);
            adjustHeightForNode(branch_node->else_node);
            branch_node->height = 1 + std::max(
                branch_node->if_node->height,
                std::max(
                    branch_node->then_node->height,
                    branch_node->else_node->height
                )
            );
            return;
        }

    }
}

void TBGPNodeDepthAdjuster::adjustMaxDepthForNode(TBGPNode* node, int max_depth) {
        switch (node->node_type)
    {

    case ABSTRACT:
        {
            return;
        }
    case CONST:
        {
            auto const_node = dynamic_cast<TBGPNodeConst*>(node);
            const_node->max_depth = max_depth;
            return;
        }

    case PARAM:
        {
            auto param_node = dynamic_cast<TBGPNodeParam*>(node);
            param_node->max_depth = max_depth;
            return;
        }

    case UNARY_MINUS:
        {
            auto unary_minus_node = dynamic_cast<TBGPNodeUnaryMinus*>(node);
            unary_minus_node->max_depth = max_depth;
            adjustMaxDepthForNode(unary_minus_node->operand_node, max_depth - 1);
            return;
        }

    case PLUS:
        {
            auto plus_node = dynamic_cast<TBGPNodePlus*>(node);
            plus_node->max_depth = max_depth;
            adjustMaxDepthForNode(plus_node->first_summand_node, max_depth - 1);
            adjustMaxDepthForNode(plus_node->second_summand_node, max_depth - 1);
            return;
        }

    case MINUS:
        {
            auto minus_node = dynamic_cast<TBGPNodeMinus*>(node);
            minus_node->max_depth = max_depth;
            adjustMaxDepthForNode(minus_node->minuend_node, max_depth - 1);
            adjustMaxDepthForNode(minus_node->subtrahend_node, max_depth - 1);
            return;
        }

    case TIMES:
        {
            auto times_node = dynamic_cast<TBGPNodeTimes*>(node);
            times_node->max_depth = max_depth;
            adjustMaxDepthForNode(times_node->first_factor_node, max_depth - 1);
            adjustMaxDepthForNode(times_node->second_factor_node, max_depth - 1);
            return;
        }

    case DIVIDE:
        {
            auto divide_node = dynamic_cast<TBGPNodeDivide*>(node);
            divide_node->max_depth = max_depth;
            adjustMaxDepthForNode(divide_node->dividend_node, max_depth - 1);
            adjustMaxDepthForNode(divide_node->divisor_node, max_depth - 1);
            return;
        }

    case SQUARE:
        {
            auto square_node = dynamic_cast<TBGPNodeSquare*>(node);
            square_node->max_depth = max_depth;
            adjustMaxDepthForNode(square_node->base_node, max_depth - 1);
            return;
        }

    case ROOT:
        {
            auto root_node = dynamic_cast<TBGPNodeRoot*>(node);
            root_node->max_depth = max_depth;
            adjustMaxDepthForNode(root_node->radicand_node, max_depth - 1);
            return;
        }

    case BRANCH:
        {
            auto branch_node = dynamic_cast<TBGPNodeBranch*>(node);
            branch_node->max_depth = max_depth;
            adjustMaxDepthForNode(branch_node->if_node, max_depth - 1);
            adjustMaxDepthForNode(branch_node->then_node, max_depth - 1);
            adjustMaxDepthForNode(branch_node->else_node, max_depth - 1);
            return;
        }

    }
}

