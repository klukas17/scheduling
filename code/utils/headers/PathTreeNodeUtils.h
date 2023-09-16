//
// Created by mihael on 9/3/23.
//

/**
 * @file PathTreeNodeUtils.h
 * @brief Defines the PathTreeNodeUtils class for providing utility functions for logging path tree node objects.
 */

#ifndef SCHEDULING_PATHTREENODEUTILS_H
#define SCHEDULING_PATHTREENODEUTILS_H

#include "Job.h"
#include "map"
#include "string"
#include "fstream"

/**
 * @class PathTreeNodeUtils
 * @brief Provides utility functions for logging path tree node objects.
 *
 * The PathTreeNodeUtils class offers static utility functions to assist in logging information about path tree nodes.
 */
class PathTreeNodeUtils {
public:
    /**
     * @brief Logs information about path tree nodes for a set of jobs.
     *
     * This function logs information about path tree nodes for a set of jobs to a specified log file.
     *
     * @param jobs A map of job IDs to Job objects.
     * @param logs_path The path to the log file where the information will be logged.
     */
    static void logPathTreeNodes(std::map<long, Job*> jobs, const std::string& logs_path);

    /**
     * @brief Logs information about a single path tree node.
     *
     * This function logs information about a single path tree node, including its details and sub-nodes,
     * with specified indentation to a log stream.
     *
     * @param path_tree_node A pointer to the PathTreeNode to be logged.
     * @param indents The number of indents to apply for formatting.
     * @param log_stream The output log stream where the information will be logged.
     */
    static void logPathTreeNode(PathTreeNode* path_tree_node, int indents, std::ofstream& log_stream);
};


#endif //SCHEDULING_PATHTREENODEUTILS_H
