//
// Created by mihael on 07/05/23.
//

#include "JobProcessingStep.h"

JobProcessingStep::JobProcessingStep(long const processing_step_id, long const machine_id, long const job_id, long const path_node_id) {
    this->processing_step_id = processing_step_id;
    this->machine_id = machine_id;
    this->job_id = job_id;
    this->path_node_id = path_node_id;
}

long JobProcessingStep::getProcessingStepId() const {
    return processing_step_id;
}

long JobProcessingStep::getMachineId() const {
    return machine_id;
}

long JobProcessingStep::getJobId() const {
    return job_id;
}

long JobProcessingStep::getPathNodeId() const {
    return path_node_id;
}