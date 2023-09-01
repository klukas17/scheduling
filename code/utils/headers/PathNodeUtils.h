//
// Created by mihael on 8/19/23.
//

/**
 * @file PathNodeUtils.h
 * @brief Defines the PathNodeUtils class for providing utility functions for logging path node objects.
 */

#ifndef SCHEDULING_PATHNODEUTILS_H
#define SCHEDULING_PATHNODEUTILS_H

#include "Job.h"
#include "string"
#include "deque"
#include "fstream"

/**
 * @class PathNodeUtils
 * @brief Provides utility functions for logging path node objects.
 *
 * The PathNodeUtils class offers static utility functions to assist in logging information about path nodes.
 */
class PathNodeUtils {
public:
    /**
     * @brief Logs information about path nodes to a specified file.
     *
     * This function logs details about path nodes, including job information, to a file specified by the `logs_path`.
     *
     * @param jobs A map of job IDs to Job objects representing the jobs to be logged.
     * @param logs_path The path where the log file will be saved.
     */
    static void logPathNodes(std::map<long, Job*> jobs, const std::string& logs_path);

    /**
     * @brief Logs information about a single path node to a log stream.
     *
     * This function logs details about a single path node, including its properties and associated job information,
     * to the provided output stream `log_stream`. The information is stored in a deque for traversal purposes.
     *
     * @param path_node A pointer to the PathNode to be logged.
     * @param path_node_deque A deque used for path node traversal and logging order.
     * @param log_stream The output stream where the log information is written.
     */
    static void logPathNode(PathNode* path_node, std::deque<long>& path_node_deque, std::ofstream& log_stream);
};

#endif //SCHEDULING_PATHNODEUTILS_H
