//
// Created by mihael on 5/22/24.
//

#include "TBGPNodeReplacer.h"

#include "TBGPNodeBranch.h"
#include "TBGPNodeDivide.h"
#include "TBGPNodeMinus.h"
#include "TBGPNodePlus.h"
#include "TBGPNodeRoot.h"
#include "TBGPNodeSquare.h"
#include "TBGPNodeTimes.h"
#include "TBGPNodeUnaryMinus.h"

void TBGPNodeReplacer::replaceChildren(TBGPNode* parent, TBGPNode* former_child, TBGPNode* new_child) {

    switch(parent->node_type)
    {

    case TBGP_ABSTRACT:
    case TBGP_CONST:
    case TBGP_PARAM:
        {
            break;
        }

    case TBGP_UNARY_MINUS:
        {
            auto unary_minus_node = dynamic_cast<TBGPNodeUnaryMinus*>(parent);
            if (unary_minus_node->operand_node == former_child) {
                unary_minus_node->operand_node = new_child;
            }
            break;
        }

    case TBGP_PLUS:
        {
            auto plus_node = dynamic_cast<TBGPNodePlus*>(parent);
            if (plus_node->first_summand_node == former_child) {
                plus_node->first_summand_node = new_child;
            }
            if (plus_node->second_summand_node == former_child) {
                plus_node->second_summand_node = new_child;
            }
            break;
        }

    case TBGP_MINUS:
        {
            auto minus_node = dynamic_cast<TBGPNodeMinus*>(parent);
            if (minus_node->minuend_node == former_child) {
                minus_node->minuend_node = new_child;
            }
            if (minus_node->subtrahend_node == former_child) {
                minus_node->subtrahend_node = new_child;
            }
            break;
        }

    case TBGP_TIMES:
        {
            auto times_node = dynamic_cast<TBGPNodeTimes*>(parent);
            if (times_node->first_factor_node == former_child) {
                times_node->first_factor_node = new_child;
            }
            if (times_node->second_factor_node == former_child) {
                times_node->second_factor_node = new_child;
            }
            break;
        }

    case TBGP_DIVIDE:
        {
            auto divide_node = dynamic_cast<TBGPNodeDivide*>(parent);
            if (divide_node->dividend_node == former_child) {
                divide_node->dividend_node = new_child;
            }
            if (divide_node->divisor_node == former_child) {
                divide_node->divisor_node = new_child;
            }
            break;
        }

    case TBGP_SQUARE:
        {
            auto square_node = dynamic_cast<TBGPNodeSquare*>(parent);
            if (square_node->base_node == former_child) {
                square_node->base_node = new_child;
            }
            break;
        }

    case TBGP_ROOT:
        {
            auto root_node = dynamic_cast<TBGPNodeRoot*>(parent);
            if (root_node->radicand_node == former_child) {
                root_node->radicand_node = new_child;
            }
            break;
        }

    case TBGP_BRANCH:
        {
            auto branch_node = dynamic_cast<TBGPNodeBranch*>(parent);
            if (branch_node->if_node == former_child) {
                branch_node->if_node = new_child;
            }
            if (branch_node->then_node == former_child) {
                branch_node->then_node = new_child;
            }
            if (branch_node->else_node == former_child) {
                branch_node->else_node = new_child;
            }
            break;
        }
    }
}
