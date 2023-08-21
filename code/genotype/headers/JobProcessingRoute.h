//
// Created by mihael on 07/05/23.
//

/**
 * @file JobProcessingRoute.h
 * @brief Defines the JobProcessingRoute class for representing a sequence of processing steps for a job.
 */

#ifndef SCHEDULING_JOBPROCESSINGROUTE_H
#define SCHEDULING_JOBPROCESSINGROUTE_H

#include "vector"
#include "JobProcessingStep.h"

/**
 * @class JobProcessingRoute
 * @brief Represents a sequence of processing steps for a job.
 *
 * The JobProcessingRoute class encapsulates information about a sequence of processing steps that a job goes through.
 * It includes the job's identifier, a vector of associated processing steps, and the count of steps.
 */
class JobProcessingRoute {
private:
    long job_id; /**< Identifier for the job. */
    std::vector<JobProcessingStep*> processing_steps; /**< Vector of associated processing steps. */
public:
    /**
     * @brief Constructs a JobProcessingRoute object for the specified job.
     * @param job_id The identifier for the job.
     */
    explicit JobProcessingRoute(long job_id);

    /**
     * @brief Retrieves the identifier for the job.
     * @return The identifier for the job.
     */
    [[nodiscard]] long getJobId() const;

    /**
     * @brief Adds a processing step to the route.
     * @param processing_step A pointer to the processing step to be added.
     */
    void addProcessingStep(JobProcessingStep* processing_step);

    /**
     * @brief Retrieves the vector of processing steps in the route.
     * @return A vector containing pointers to the associated processing steps.
     */
    std::vector<JobProcessingStep*> getProcessingSteps();

    /**
     * @brief Retrieves a specific processing step from the route by index.
     * @param index The index of the desired processing step.
     * @return A pointer to the processing step at the specified index.
     */
    JobProcessingStep* getProcessingStep(long index);
};

#endif //SCHEDULING_JOBPROCESSINGROUTE_H

