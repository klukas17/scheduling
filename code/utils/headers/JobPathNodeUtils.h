//
// Created by mihael on 8/19/23.
//

/**
 * @file JobPathNodeUtils.h
 * @brief Defines the JobPathNodeUtils class for providing utility functions for logging job path nodes.
 */

#ifndef SCHEDULING_JOBPATHNODEUTILS_H
#define SCHEDULING_JOBPATHNODEUTILS_H

#include "Job.h"
#include "string"
#include "deque"
#include "fstream"

/**
 * @class JobPathNodeUtils
 * @brief Provides utility functions for logging job path nodes.
 *
 * The JobPathNodeUtils class offers static utility functions to assist in logging information about job path nodes
 * and their corresponding details.
 */
class JobPathNodeUtils {
public:
    /**
     * @brief Logs information about a map of job path nodes to an output file.
     *
     * This function logs information about each job path node in the provided map to an output file specified by the
     * 'logs_path'. It logs details such as job IDs and related information.
     *
     * @param jobs A map of job IDs to Job pointers representing job path nodes.
     * @param logs_path The path to the output log file.
     */
    static void logJobPathNodes(std::map<long, Job*> jobs, const std::string& logs_path);

    /**
     * @brief Logs information about a single job path node and its related path.
     *
     * This function logs information about a specific job path node along with the sequence of job IDs in the
     * 'job_path_deque' to an output log stream provided by 'log_stream'.
     *
     * @param job_path_node A pointer to the job path node to be logged.
     * @param job_path_deque A deque containing the sequence of job IDs in the path.
     * @param log_stream The output log stream to write the information to.
     */
    static void logJobPathNode(JobPathNode* job_path_node, std::deque<long>& job_path_deque, std::ofstream& log_stream);
};

#endif //SCHEDULING_JOBPATHNODEUTILS_H

