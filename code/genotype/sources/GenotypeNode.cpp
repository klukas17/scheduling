//
// Created by mihael on 29/04/23.
//

/**
 * @file GenotypeNode.cpp
 * @brief Implements the member functions of the GenotypeNode class.
 */

#include "GenotypeNode.h"

GenotypeNode::GenotypeNode(long id) {
    this->id = id;
    this->node_type = ABSTRACT_NODE;
    this->general_node_type = ABSTRACT_GENERAL_NODE;
}

GenotypeNode::~GenotypeNode() = default;

long GenotypeNode::getId() const {
    return id;
}

NodeType GenotypeNode::getNodeType() {
    return node_type;
}

GeneralNodeType GenotypeNode::getGeneralNodeType() {
    return general_node_type;
}

std::vector<long> GenotypeNode::getStepProcessingOrder() {
    return step_processing_order;
}

void GenotypeNode::addStep(long step_id) {
    step_processing_order.push_back(step_id);
}

std::set<long> GenotypeNode::getPredecessorIds() {
    return predecessor_node_ids;
}

void GenotypeNode::addPredecessorId(long node_id) {
    predecessor_node_ids.insert(node_id);
}