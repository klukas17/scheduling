//
// Created by mihael on 29/04/23.
//

#include "Job.h"

Job::Job(long id, JobType* job_type, long release_date, long due_date, long weight) {
    this->id = id;
    this->job_type = job_type;
    this->release_date = release_date;
    this->due_date = due_date;
    this->weight = weight;
}

long Job::getId() const {
    return id;
}

JobType *Job::getJobType() {
    return job_type;
}

long Job::getReleaseDate() {
    return release_date;
}

long Job::getDueDate() {
    return due_date;
}

long Job::getWeight() {
    return weight;
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