//
// Created by mihael on 30/04/23.
//

#include "SerialGroupNode.h"

SerialGroupNode::SerialGroupNode(long id) : GenotypeNode(id) {
    this->node_type = SERIAL_GROUP_NODE_TYPE;
}

std::vector<GenotypeNode *> SerialGroupNode::getBody() {
    return body;
}

void SerialGroupNode::addNodeToBody(GenotypeNode *node) {
    body.push_back(node);
}