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
#include "map"
#include "JobProcessingStep.h"

/**
 * @class JobProcessingRoute
 * @brief Represents a sequence of processing steps for a job.
 *
 * The JobProcessingRoute class encapsulates information about a sequence of processing steps that a job goes through.
 * It includes the job's identifier, a vector of associated processing steps, and the current step index for tracking
 * progress within the route.
 */
class JobProcessingRoute {
private:
    long job_id; /**< Identifier for the job. */
    std::vector<JobProcessingStep*> processing_steps; /**< Vector of associated processing steps. */
    std::map<long, JobProcessingStep*> processing_steps_map; /**< Map of processing steps with their IDs as keys. */
    long current_index; /**< Current step index for tracking progress within the route. */
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
     * @brief Retrieves the next processing step in the route.
     * @return A pointer to the next processing step in the route.
     */
    JobProcessingStep* getNextProcessingStep();

    /**
     * @brief Retrieves a processing step by its identifier.
     * @param step_id The identifier of the processing step to retrieve.
     * @return A pointer to the processing step, or nullptr if not found.
     */
    JobProcessingStep* getProcessingStep(long step_id);

    /**
     * @brief Checks if the route has finished all processing steps.
     * @return true if the route has finished, false otherwise.
     */
    bool checkHasFinished();

    /**
     * @brief Resets the current step index to the beginning of the route.
     */
    void resetCurrentIndex();
};

#endif //SCHEDULING_JOBPROCESSINGROUTE_H

