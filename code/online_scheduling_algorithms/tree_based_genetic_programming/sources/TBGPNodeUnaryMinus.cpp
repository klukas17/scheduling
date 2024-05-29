//
// Created by mihael on 5/21/24.
//

#include "TBGPNodeUnaryMinus.h"

TBGPNodeUnaryMinus::TBGPNodeUnaryMinus() {
    this->node_type = TBGP_UNARY_MINUS;
    operand_node = nullptr;
}

TBGPNodeUnaryMinus::~TBGPNodeUnaryMinus() {
    delete operand_node;
}

TBGPNode* TBGPNodeUnaryMinus::copy() {
    auto copy = new TBGPNodeUnaryMinus();
    copy->operand_node = operand_node->copy();
    copy->operand_node->parent = copy;
    copy->height = height;
    copy->max_depth = max_depth;
    return copy;
}

double TBGPNodeUnaryMinus::eval(std::map<std::string, double>& params) {
    return -operand_node->eval(params);
}

