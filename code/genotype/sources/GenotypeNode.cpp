//
// Created by mihael on 29/04/23.
//

#include "GenotypeNode.h"

GenotypeNode::GenotypeNode(long const id) {
    this->id = id;
    this->node_type = ABSTRACT_NODE;
    this->general_node_type = ABSTRACT_GENERAL_NODE;
}

GenotypeNode::~GenotypeNode() = default;

long GenotypeNode::getId() const {
    return id;
}

NodeType GenotypeNode::getNodeType() const {
    return node_type;
}

GeneralNodeType GenotypeNode::getGeneralNodeType() const {
    return general_node_type;
}

std::vector<long> GenotypeNode::getStepProcessingOrder() {
    return step_processing_order;
}

void GenotypeNode::addStep(long const step_id) {
    step_processing_order.push_back(step_id);
}