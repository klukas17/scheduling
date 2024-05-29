//
// Created by mihael on 5/21/24.
//

#include "TBGPNodePlus.h"

TBGPNodePlus::TBGPNodePlus() {
    this->node_type = TBGP_PLUS;
    first_summand_node = second_summand_node = nullptr;
}

TBGPNodePlus::~TBGPNodePlus() {
    delete first_summand_node;
    delete second_summand_node;
}

TBGPNode* TBGPNodePlus::copy() {
    auto copy = new TBGPNodePlus();
    copy->first_summand_node = first_summand_node->copy();
    copy->second_summand_node = second_summand_node->copy();
    copy->first_summand_node->parent = copy;
    copy->second_summand_node->parent = copy;
    copy->height = height;
    copy->max_depth = max_depth;
    return copy;
}

double TBGPNodePlus::eval(std::map<std::string, double>& params) {
    return first_summand_node->eval(params) + second_summand_node->eval(params);
}
