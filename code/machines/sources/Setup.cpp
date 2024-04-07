//
// Created by mihael on 9/19/23.
//

#include "Setup.h"

Setup::Setup(JobType *job_type_from, JobType *job_type_to, double const duration) {
    this->job_type_from = job_type_from;
    this->job_type_to = job_type_to;
    this->duration = duration;
}

JobType *Setup::getJobTypeFrom() const {
    return job_type_from;
}

JobType *Setup::getJobTypeTo() const {
    return job_type_to;
}

double Setup::getDuration() const {
    return duration;
}