//
// Created by mihael on 30/04/23.
//

#include "SerialGroupNode.h"

SerialGroupNode::SerialGroupNode(long id) : GenotypeNode(id) {
    this->node_type = SERIAL_GROUP_NODE_TYPE;
}

std::vector<long> SerialGroupNode::getJobProcessingOrder() {
    return job_processing_order;
}

void SerialGroupNode::add_job(long job_id) {
    job_processing_order.push_back(job_id);
}

std::vector<GenotypeNode *> SerialGroupNode::getBody() {
    return body;
}

void SerialGroupNode::addNodeToBody(GenotypeNode *node) {
    body.push_back(node);
}