//
// Created by mihael on 5/21/24.
//

#include "TBGPNodeSquare.h"

#include <cmath>

TBGPNodeSquare::TBGPNodeSquare() {
    this->node_type = SQUARE;
    base_node = nullptr;
}

TBGPNodeSquare::~TBGPNodeSquare() {
    delete base_node;
}

TBGPNode* TBGPNodeSquare::copy() {
    auto copy = new TBGPNodeSquare();
    copy->base_node = base_node->copy();
    copy->base_node->parent = copy;
    copy->height = height;
    copy->max_depth = max_depth;
    return copy;
}

double TBGPNodeSquare::eval(std::map<std::string, double>& params) {
    return std::pow(base_node->eval(params), 2);
}
