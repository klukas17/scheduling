//
// Created by mihael on 29/04/23.
//

/**
 * @file Job.cpp
 * @brief Implements the member functions of the Job class.
 */

#include "Job.h"

Job::Job(long id, JobType* job_type, JobPathNode* paths_root_node, long release_time, long due_time, long weight) {
    this->id = id;
    this->job_type = job_type;
    this->paths_root_node = paths_root_node;
    this->release_time = release_time;
    this->due_time = due_time;
    this->weight = weight;
}

long Job::getId() const {
    return id;
}

JobType *Job::getJobType() {
    return job_type;
}

JobPathNode *Job::getPathsRootNode() {
    return paths_root_node;
}

long Job::getReleaseTime() {
    return release_time;
}

long Job::getDueTime() {
    return due_time;
}

long Job::getWeight() {
    return weight;
}