//
// Created by mihael on 29/04/23.
//

#include "MachineNode.h"

MachineNode::MachineNode() {
    this->node_type = MACHINE_NODE_TYPE;
}

void MachineNode::add_job(long job_id) {
    this->job_processing_order.push_back(job_id);
}