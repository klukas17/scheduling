//
// Created by mihael on 4/7/24.
//

#include "JobGeneratorParameters.h"

JobGeneratorParameters::JobGeneratorParameters(
    long const job_type,
    long const number_of_jobs,
    DoubleGenerator* release_time_generator,
    double const expected_duration,
    DoubleGenerator* weight_generator
) {
    this->job_type = job_type;
    this->number_of_jobs = number_of_jobs;
    this->release_time_generator = release_time_generator;
    this->expected_duration = expected_duration;
    this->weight_generator = weight_generator;
}

long JobGeneratorParameters::getJobType() const {
    return job_type;
}

long JobGeneratorParameters::getNumberOfJobs() const {
    return number_of_jobs;
}

double JobGeneratorParameters::generateReleaseTime() const {
    return release_time_generator->generate();
}

double JobGeneratorParameters::getExpectedDuration() const {
    return expected_duration;
}

double JobGeneratorParameters::generateWeight() const {
    return weight_generator->generate();
}
