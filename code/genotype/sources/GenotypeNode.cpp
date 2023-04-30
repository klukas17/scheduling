//
// Created by mihael on 29/04/23.
//

#include "GenotypeNode.h"

GenotypeNode::GenotypeNode(long id) {
    this->id = id;
    this->node_type = ABSTRACT_NODE_TYPE;
}

GenotypeNode::~GenotypeNode() = default;

long GenotypeNode::getId() const {
    return id;
}

NodeType GenotypeNode::getNodeType() {
    return node_type;
}