//
// Created by mihael on 29/04/23.
//

/**
 * @file JobSpecificationsParser.h
 * @brief Defines the JobSpecificationsParser class for parsing job specifications from a file.
 */

#ifndef SCHEDULING_JOBSPECIFICATIONSPARSER_H
#define SCHEDULING_JOBSPECIFICATIONSPARSER_H

#include <string>
#include <map>
#include "JobType.h"
#include "JobTypeMap.h"

/**
 * @class JobSpecificationsParser
 * @brief Parses job specifications from a file.
 *
 * The JobSpecificationsParser class is responsible for reading job specifications from a file and
 * creating a map of job IDs to corresponding JobType pointers.
 */
class JobSpecificationsParser {
public:
    /**
     * @brief Parses job specifications from the specified file and returns a map of job IDs to JobType pointers.
     * @param path The path to the file containing job specifications.
     * @return A map of job IDs to JobType pointers.
     * @throws SchedulingError if the 'jobs' key is not found in the file or an entry in the 'jobs' array is missing the 'job_id' field.
     */
    static JobTypeMap* parse(const std::string& path);

};

#endif //SCHEDULING_JOBSPECIFICATIONSPARSER_H

