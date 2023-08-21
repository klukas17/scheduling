//
// Created by mihael on 07/05/23.
//

/**
 * @file JobProcessingRoute.cpp
 * @brief Implements the member functions of the JobProcessingRoute class.
 */

#include "JobProcessingRoute.h"

JobProcessingRoute::JobProcessingRoute(long job_id) {
    this->job_id = job_id;
}

long JobProcessingRoute::getJobId() const {
    return job_id;
}

void JobProcessingRoute::addProcessingStep(JobProcessingStep *processing_step) {
    processing_steps.push_back(processing_step);
}

std::vector<JobProcessingStep *> JobProcessingRoute::getProcessingSteps() {
    return processing_steps;
}

JobProcessingStep *JobProcessingRoute::getProcessingStep(long index) {
    if (index < 0 || index >= processing_steps.size())
        return nullptr;
    return processing_steps[index];
}