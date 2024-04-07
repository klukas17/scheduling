//
// Created by mihael on 10/1/23.
//

#include "BatchProcessingScenario.h"

BatchProcessingScenario::BatchProcessingScenario(JobType *job_type, long const jobs_per_batch) {
    this->job_type = job_type;
    this->jobs_per_batch = jobs_per_batch;
}

JobType *BatchProcessingScenario::getJobType() const {
    return job_type;
}

long BatchProcessingScenario::getJobsPerBatch() const {
    return jobs_per_batch;
}