//
// Created by mihael on 30/04/23.
//

#include "JobRoute.h"
#include <utility>
#include "MachineNode.h"

JobRoute::JobRoute(Job *job, JobProcessingRoute* job_processing_route) {
    this->job = job;
    this->job_processing_route = job_processing_route;
    this->current_index = 0;
}

JobProcessingRoute *JobRoute::getProcessingRoute() {
    return job_processing_route;
}

JobProcessingStep *JobRoute::getNextProcessingStep() {
    long index = current_index;
    current_index++;
    return job_processing_route->getProcessingStep(index);
}

long JobRoute::getCurrentIndex() const {
    return current_index;
}

bool JobRoute::checkHasFinished() {
    return current_index == job_processing_route->getStepCount();
}