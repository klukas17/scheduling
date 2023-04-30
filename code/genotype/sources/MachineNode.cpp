//
// Created by mihael on 29/04/23.
//

#include "MachineNode.h"

MachineNode::MachineNode(long id) : GenotypeNode(id) {
    this->node_type = MACHINE_NODE_TYPE;
}

std::vector<long> MachineNode::getJobProcessingOrder() {
    return job_processing_order;
}

void MachineNode::add_job(long job_id) {
    job_processing_order.push_back(job_id);
}