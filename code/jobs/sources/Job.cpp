//
// Created by mihael on 29/04/23.
//

#include "Job.h"

Job::Job(long id, JobType *job_type) {
    this->id = id;
    this->job_type = job_type;
}

long Job::getId() const {
    return id;
}

JobType *Job::getJobType() {
    return job_type;
}

std::vector<long> Job::getProcessingRoute() {
    return processing_route;
}

void Job::addMachineToProcessingRoute(long machine_id) {
    processing_route.push_back(machine_id);
}

long Job::getProcessingTime(long machine_id) {
    return processing_times[machine_id];
}

void Job::setProcessingTime(long machine_id, long processing_time) {
    processing_times[machine_id] = processing_time;
}