//
// Created by mihael on 5/21/24.
//

#include "TBGPNodeMinus.h"

TBGPNodeMinus::TBGPNodeMinus() {
    this->node_type = MINUS;
    minuend_node = subtrahend_node = nullptr;
}

TBGPNodeMinus::~TBGPNodeMinus() {
    delete minuend_node;
    delete subtrahend_node;
}

TBGPNode* TBGPNodeMinus::copy() {
    auto copy = new TBGPNodeMinus();
    copy->minuend_node = minuend_node->copy();
    copy->subtrahend_node = subtrahend_node->copy();
    copy->minuend_node->parent = copy;
    copy->subtrahend_node->parent = copy;
    copy->height = height;
    copy->max_depth = max_depth;
    return copy;
}


double TBGPNodeMinus::eval(std::map<std::string, double>& params) {
    return minuend_node->eval(params) - subtrahend_node->eval(params);
}

