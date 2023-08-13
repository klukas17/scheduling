//
// Created by mihael on 8/13/23.
//

/**
 * @file JobTypeMap.h
 * @brief Defines the JobTypeMap class for representing a map of all job types.
 */

#ifndef SCHEDULING_JOBTYPEMAP_H
#define SCHEDULING_JOBTYPEMAP_H

#include <map>
#include "JobType.h"

/**
 * @class JobTypeMap
 * @brief Class for representing a map of all job types.
 */
class JobTypeMap {
private:
    std::map<long, JobType*> job_type_map; /**< The map of job types with their IDs as keys */

public:
    /**
     * @brief Constructs an empty JobTypeMap object.
     */
    JobTypeMap();

    /**
     * @brief Gets the map of job types.
     * @return The map of job types with their IDs as keys.
     */
    std::map<long, JobType*> getJobTypeMap();

    /**
     * @brief Gets the job type with the specified ID.
     * @param job_type_id The ID of the job type to retrieve.
     * @return A pointer to the JobType object, or nullptr if not found.
     */
    JobType* getJobType(long job_type_id);

    /**
     * @brief Adds a job type to the map.
     * @param job_type_id The ID of the job type to add.
     * @param job_type A pointer to the JobType object to add.
     * @throws SchedulingError if an entry with the key job_type_id is already present in the map.
     */
    void addJobType(long job_type_id, JobType* job_type);
};

#endif // SCHEDULING_JOBTYPEMAP_H

