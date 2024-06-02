//
// Created by mihael on 5/21/24.
//

#include "TBGPNodeBranch.h"

TBGPNodeBranch::TBGPNodeBranch() {
    this->node_type = TBGP_BRANCH;
    if_node = then_node = else_node = nullptr;
}

TBGPNodeBranch::~TBGPNodeBranch() {
    delete if_node;
    delete then_node;
    delete else_node;
}

TBGPNode* TBGPNodeBranch::copy() {
    auto copy = new TBGPNodeBranch();
    copy->if_node = if_node->copy();
    copy->then_node = then_node->copy();
    copy->else_node = else_node->copy();
    copy->if_node->parent = copy;
    copy->then_node->parent = copy;
    copy->then_node->parent = copy;
    copy->height = height;
    copy->max_depth = max_depth;
    return copy;
}

double TBGPNodeBranch::eval(std::map<std::string, double>& params) {
    return if_node->eval(params) >= 0 ? then_node->eval(params) : else_node->eval(params);
}
