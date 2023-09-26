//
// Created by mihael on 9/19/23.
//

/**
 * @file Setup.cpp
 * @brief Implements the member functions of the Setup class.
 */

#include "Setup.h"

Setup::Setup(JobType *job_type_from, JobType *job_type_to, long duration) {
    this->job_type_from = job_type_from;
    this->job_type_to = job_type_to;
    this->duration = duration;
}

JobType *Setup::getJobTypeFrom() {
    return job_type_from;
}

JobType *Setup::getJobTypeTo() {
    return job_type_to;
}

long Setup::getDuration() const {
    return duration;
}