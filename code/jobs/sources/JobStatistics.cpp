//
// Created by mihael on 2/11/24.
//

#include "JobStatistics.h"

JobStatistics::JobStatistics(long const id, double const release_time, double const due_time, double const weight) {
    this->id = id;
    this->release_time = release_time;
    this->due_time = due_time;
    this->weight = weight;
    this->exit_time = 0;
    this->job_status = UNTERMINATED;
}

long JobStatistics::getId() const {
    return id;
}

double JobStatistics::getReleaseTime() const {
    return release_time;
}

double JobStatistics::getDueTime() const {
    return due_time;
}

double JobStatistics::getWeight() const {
    return weight;
}

double JobStatistics::getExitTime() const {
    return exit_time;
}

JobStatus JobStatistics::getJobStatus() const {
    return job_status;
}

void JobStatistics::setExitTime(double const exit_time) {
    this->exit_time = exit_time;
}

void JobStatistics::setJobStatus(JobStatus const job_status) {
    this->job_status = job_status;
}
