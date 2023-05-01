//
// Created by mihael on 01/05/23.
//

#include "ParallelGroupNode.h"

ParallelGroupNode::ParallelGroupNode(long id) : GenotypeNode(id) {
    this->node_type = PARALLEL_GROUP_NODE_TYPE;
}

std::vector<GenotypeNode *> ParallelGroupNode::getBody() {
    return body;
}

void ParallelGroupNode::addNodeToBody(GenotypeNode *node) {
    body.push_back(node);
}