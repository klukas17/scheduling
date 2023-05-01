//
// Created by mihael on 29/04/23.
//

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

std::vector<long> GenotypeNode::getJobProcessingOrder() {
    return job_processing_order;
}

void GenotypeNode::addJob(long job_id) {
    job_processing_order.push_back(job_id);
}