//
// Created by mihael on 5/21/24.
//

#include "TBGPNodeRoot.h"
#include <cmath>

TBGPNodeRoot::TBGPNodeRoot() {
    this->node_type = TBGP_ROOT;
    radicand_node = nullptr;
}

TBGPNodeRoot::~TBGPNodeRoot() {
    delete radicand_node;
}

TBGPNode* TBGPNodeRoot::copy() {
    auto copy = new TBGPNodeRoot();
    copy->radicand_node = radicand_node->copy();
    copy->radicand_node->parent = copy;
    copy->height = height;
    copy->max_depth = max_depth;
    return copy;
}

double TBGPNodeRoot::eval(std::map<std::string, double>& params) {
    return std::sqrt(std::abs(radicand_node->eval(params)));
}
