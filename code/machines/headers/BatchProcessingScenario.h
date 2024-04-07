//
// Created by mihael on 10/1/23.
//


#ifndef SCHEDULING_BATCHPROCESSINGSCENARIO_H
#define SCHEDULING_BATCHPROCESSINGSCENARIO_H

#include "JobType.h"

class BatchProcessingScenario {
    JobType* job_type;
    long jobs_per_batch;

public:
    BatchProcessingScenario(JobType* job_type, long jobs_per_batch);
    [[nodiscard]] JobType* getJobType() const;
    [[nodiscard]] long getJobsPerBatch() const;
};

#endif //SCHEDULING_BATCHPROCESSINGSCENARIO_H
