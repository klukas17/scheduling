//
// Created by mihael on 01/05/23.
//

#include "GroupNode.h"

GroupNode::GroupNode(long id) : GenotypeNode(id) {
    this->general_node_type = GROUP_GENERAL_NODE;
}

std::vector<GenotypeNode *> GroupNode::getBody() {
    return body;
}

void GroupNode::addNodeToBody(GenotypeNode *node) {
    body.push_back(node);
}