//
// Created by mihael on 01/05/23.
//

/**
 * @file GroupNode.cpp
 * @brief Implements the member functions of the GroupNode class.
 */

#include "GroupNode.h"

GroupNode::GroupNode(long id) : GenotypeNode(id) {
    this->general_node_type = GROUP_GENERAL_NODE;
}

GroupNode::~GroupNode() = default;

std::vector<GenotypeNode *> GroupNode::getBody() {
    return body;
}

void GroupNode::addNodeToBody(GenotypeNode *node) {
    body.push_back(node);
}