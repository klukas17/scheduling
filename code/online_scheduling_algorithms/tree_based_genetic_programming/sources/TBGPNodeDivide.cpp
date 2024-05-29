//
// Created by mihael on 5/21/24.
//

#include "TBGPNodeDivide.h"

TBGPNodeDivide::TBGPNodeDivide() {
    this->node_type = TBGP_DIVIDE;
    dividend_node = divisor_node = nullptr;
}

TBGPNodeDivide::~TBGPNodeDivide() {
    delete dividend_node;
    delete divisor_node;
}

TBGPNode* TBGPNodeDivide::copy() {
    auto copy = new TBGPNodeDivide();
    copy->dividend_node = dividend_node->copy();
    copy->divisor_node = divisor_node->copy();
    copy->dividend_node->parent = copy;
    copy->divisor_node->parent = copy;
    copy->height = height;
    copy->max_depth = max_depth;
    return copy;
}

double TBGPNodeDivide::eval(std::map<std::string, double>& params) {
    auto divisor = dividend_node->eval(params);
    if (divisor >= -1e-6 && divisor <= 1e-6) {
        return 1;
    }
    return dividend_node->eval(params) / divisor;
}
