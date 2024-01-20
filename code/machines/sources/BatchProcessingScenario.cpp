//
// Created by mihael on 10/1/23.
//

/**
 * @file BatchProcessingScenario.cpp
 * @brief Implements the member functions of the BatchProcessingScenario class.
 */

#include "BatchProcessingScenario.h"

BatchProcessingScenario::BatchProcessingScenario(JobType *job_type, long jobs_per_batch) {
    this->job_type = job_type;
    this->jobs_per_batch = jobs_per_batch;
}

JobType *BatchProcessingScenario::getJobType() {
    return job_type;
}

long BatchProcessingScenario::getJobsPerBatch() const {
    return jobs_per_batch;
}