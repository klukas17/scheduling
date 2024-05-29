//
// Created by mihael on 5/21/24.
//

#include "TBGPNode.h"

TBGPNode::TBGPNode() {
    this->height = 0;
    this->max_depth = 0;
    this->parent = nullptr;
    this->node_type = TBGP_ABSTRACT;
}

TBGPNode::~TBGPNode() = default;

