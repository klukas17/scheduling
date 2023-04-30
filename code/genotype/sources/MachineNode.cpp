//
// Created by mihael on 29/04/23.
//

#include "MachineNode.h"

MachineNode::MachineNode(long id) {
    this->id = id;
    this->node_type = MACHINE_NODE_TYPE;
}

long MachineNode::getId() {
    return id;
}

void MachineNode::add_job(long job_id) {
    this->job_processing_order.push_back(job_id);
}

std::vector<long> MachineNode::getJobProcessingOrder() {
    return job_processing_order;
}