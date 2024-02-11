//
// Created by mihael on 2/11/24.
//

#include "JobStatistics.h"

JobStatistics::JobStatistics(long id, long release_time, long due_time, long weight) {
    this->id = id;
    this->release_time = release_time;
    this->due_time = due_time;
    this->weight = weight;
    this->exit_time = 0;
    this->job_status = UNTERMINATED;
}

long JobStatistics::getId() {
    return id;
}

long JobStatistics::getReleaseTime() {
    return release_time;
}

long JobStatistics::getDueTime() {
    return due_time;
}

long JobStatistics::getWeight() {
    return weight;
}

long JobStatistics::getExitTime() {
    return exit_time;
}

JobStatus JobStatistics::getJobStatus() {
    return job_status;
}

void JobStatistics::setExitTime(long exit_time) {
    this->exit_time = exit_time;
}

void JobStatistics::setJobStatus(JobStatus job_status) {
    this->job_status = job_status;
}
