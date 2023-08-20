//
// Created by mihael on 29/04/23.
//

/**
 * @file Job.h
 * @brief Defines the Job class for representing a job with its characteristics and attributes.
 */

#ifndef SCHEDULING_JOB_H
#define SCHEDULING_JOB_H

#include "JobType.h"
#include "JobPathNode.h"
#include "map"
#include "vector"

/**
 * @class Job
 * @brief Represents a job with its characteristics and attributes.
 *
 * The Job class encapsulates information about a job, including its unique ID, associated job type,
 * paths root node, release time, due time, and weight. It provides access methods to retrieve these attributes.
 */
class Job {
private:
    long id; /**< The unique identifier of the job. */
    JobType* job_type; /**< A pointer to the associated job type. */
    JobPathNode* paths_root_node; /**< A pointer to the root node of the job's paths. */
    long release_time; /**< The release time of the job. */
    long due_time; /**< The due time of the job. */
    long weight; /**< The weight of the job. */
public:
    /**
     * @brief Constructs a Job object with the given parameters.
     * @param id The unique identifier of the job.
     * @param job_type A pointer to the associated job type.
     * @param paths_root_node A pointer to the root node of the job's paths.
     * @param release_time The release time of the job.
     * @param due_time The due time of the job.
     * @param weight The weight of the job.
     */
    Job(long id, JobType* job_type, JobPathNode* paths_root_node, long release_time, long due_time, long weight);

    /**
     * @brief Retrieves the unique identifier of the job.
     * @return The unique identifier of the job.
     */
    [[nodiscard]] long getId() const;

    /**
     * @brief Retrieves a pointer to the associated job type.
     * @return A pointer to the associated JobType object.
     */
    JobType* getJobType();

    /**
     * @brief Retrieves a pointer to the root node of the job's paths.
     * @return A pointer to the root JobPathNode object.
     */
    JobPathNode* getPathsRootNode();

    /**
     * @brief Retrieves the release time of the job.
     * @return The release time of the job.
     */
    long getReleaseTime();

    /**
     * @brief Retrieves the due time of the job.
     * @return The due time of the job.
     */
    long getDueTime();

    /**
     * @brief Retrieves the weight of the job.
     * @return The weight of the job.
     */
    long getWeight();
};

#endif //SCHEDULING_JOB_H

