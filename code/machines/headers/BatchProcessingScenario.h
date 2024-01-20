//
// Created by mihael on 10/1/23.
//

/**
 * @file BatchProcessingScenario.h
 * @brief Defines the BatchProcessingScenario class for representing a scenario of batch processing for a specific job type.
 */

#ifndef SCHEDULING_BATCHPROCESSINGSCENARIO_H
#define SCHEDULING_BATCHPROCESSINGSCENARIO_H

#include "JobType.h"

/**
 * @class BatchProcessingScenario
 * @brief Represents a scenario of batch processing for a specific job type.
 *
 * The BatchProcessingScenario class provides functionality for defining and managing a scenario
 * where jobs of a specific type are processed in batches. It includes information about the associated
 * job type and the number of jobs processed per batch.
 */
class BatchProcessingScenario {
private:
    JobType* job_type; /**< Pointer to the JobType object associated with this batch processing scenario. */
    long jobs_per_batch; /**< The number of jobs processed per batch in this scenario. */

public:
    /**
     * @brief Constructs a BatchProcessingScenario object with the given job type and number of jobs per batch.
     * @param job_type Pointer to the JobType object associated with this batch processing scenario.
     * @param jobs_per_batch The number of jobs processed per batch in this scenario.
     */
    BatchProcessingScenario(JobType* job_type, long jobs_per_batch);

    /**
     * @brief Retrieves the job type associated with this batch processing scenario.
     * @return Pointer to the JobType object.
     */
    JobType* getJobType();

    /**
     * @brief Retrieves the number of jobs processed per batch in this scenario.
     * @return The number of jobs processed per batch.
     */
    [[nodiscard]] long getJobsPerBatch() const;
};

#endif //SCHEDULING_BATCHPROCESSINGSCENARIO_H
