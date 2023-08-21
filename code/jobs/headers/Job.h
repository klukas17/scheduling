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
 * paths root node, release time, due time, weight, and processing times on different machines.
 * It provides access methods to retrieve and manage these attributes.
 */
class Job {
private:
    long id; /**< The unique identifier of the job. */
    JobType* job_type; /**< A pointer to the associated job type. */
    std::map<long, long> processing_times; /**< Map of machine IDs to processing times on those machines. */
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
     * @brief Retrieves the map of processing times for the job on different machines.
     * @return A map containing machine IDs as keys and corresponding processing times as values.
     */
    std::map<long, long> getProcessingTimes();

    /**
     * @brief Retrieves the processing time of the job on a specific machine.
     * @param machine_id The identifier of the machine.
     * @return The processing time of the job on the specified machine.
     */
    long getProcessingTime(long machine_id);

    /**
     * @brief Adds a processing time for the job on a specific machine.
     * @param machine_id The identifier of the machine.
     * @param time The processing time of the job on the specified machine.
     */
    void addProcessingTime(long machine_id, long time);

    /**
     * @brief Retrieves a pointer to the root node of the job's paths.
     * @return A pointer to the root JobPathNode object.
     */
    JobPathNode* getPathsRootNode();

    /**
     * @brief Retrieves the release time of the job.
     * @return The release time of the job.
     */
    long getReleaseTime() const;

    /**
     * @brief Retrieves the due time of the job.
     * @return The due time of the job.
     */
    long getDueTime() const;

    /**
     * @brief Retrieves the weight of the job.
     * @return The weight of the job.
     */
    long getWeight() const;
};

#endif //SCHEDULING_JOB_H
