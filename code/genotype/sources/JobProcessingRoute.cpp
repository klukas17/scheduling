//
// Created by mihael on 07/05/23.
//

#include "JobProcessingRoute.h"

JobProcessingRoute::JobProcessingRoute(long const job_id) {
    this->job_id = job_id;
    this->current_index = 0;
}

long JobProcessingRoute::getJobId() const {
    return job_id;
}

void JobProcessingRoute::addProcessingStep(JobProcessingStep *processing_step) {
    processing_steps.push_back(processing_step);
    processing_steps_map[processing_step->getProcessingStepId()] = processing_step;
}

std::vector<JobProcessingStep *> JobProcessingRoute::getProcessingSteps() {
    return processing_steps;
}

JobProcessingStep *JobProcessingRoute::getNextProcessingStep() {
    long const index = current_index;
    current_index++;
    if (index < 0 || index >= processing_steps.size()) {
        return nullptr;
    }
    return processing_steps[index];
}

JobProcessingStep *JobProcessingRoute::getProcessingStep(long const step_id) {
    return processing_steps_map[step_id];
}

bool JobProcessingRoute::checkHasFinished() const {
    return current_index == processing_steps.size();
}

void JobProcessingRoute::resetCurrentIndex() {
    current_index = 0;
}