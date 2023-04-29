//
// Created by mihael on 29/04/23.
//

#include "Job.h"

Job::Job(long id, JobType *job_type) {
    this->id = id;
    this->job_type = job_type;
}

void Job::addMachineToProcessingRoute(long machine_id) {
    processing_route.push_back(machine_id);
}

void Job::setProcessingTime(long machine_id, long processing_time) {
    processing_times[machine_id] = processing_time;
}