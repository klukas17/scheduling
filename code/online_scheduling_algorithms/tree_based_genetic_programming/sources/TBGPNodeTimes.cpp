//
// Created by mihael on 5/21/24.
//

#include "TBGPNodeTimes.h"

TBGPNodeTimes::TBGPNodeTimes() {
    this->node_type = TBGP_TIMES;
    first_factor_node = second_factor_node = nullptr;
}

TBGPNodeTimes::~TBGPNodeTimes() {
    delete first_factor_node;
    delete second_factor_node;
}

TBGPNode* TBGPNodeTimes::copy() {
    auto copy = new TBGPNodeTimes();
    copy->first_factor_node = first_factor_node->copy();
    copy->second_factor_node = second_factor_node->copy();
    copy->first_factor_node->parent = copy;
    copy->second_factor_node->parent = copy;
    copy->height = height;
    copy->max_depth = max_depth;
    return copy;
}

double TBGPNodeTimes::eval(std::map<std::string, double>& params) {
    return first_factor_node->eval(params) * second_factor_node->eval(params);
}
