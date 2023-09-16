//
// Created by mihael on 07/05/23.
//

/**
 * @file JobProcessingStep.cpp
 * @brief Implements the member functions of the JobProcessingStep class.
 */

#include "JobProcessingStep.h"

JobProcessingStep::JobProcessingStep(long processing_step_id, long machine_id, long job_id, long path_node_id) {
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