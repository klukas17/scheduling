//
// Created by mihael on 8/19/23.
//

/**
 * @file PathNodeUtils.h
 * @brief Defines the PathNodeUtils class for providing utility functions for logging path nodes within a topology.
 */

#ifndef SCHEDULING_PATHNODEUTILS_H
#define SCHEDULING_PATHNODEUTILS_H

#include "Topology.h"
#include "string"
#include "deque"
#include "fstream"

/**
 * @class PathNodeUtils
 * @brief Provides utility functions for logging path nodes within a topology.
 *
 * The PathNodeUtils class offers static utility functions to assist in logging information about path nodes within
 * a topology and their corresponding details.
 */
class PathNodeUtils {
public:
    /**
     * @brief Logs information about path nodes in a topology to an output file.
     *
     * This function logs information about each path node within the provided topology to an output file specified
     * by the 'logs_path'. It logs details such as topology element IDs and related information.
     *
     * @param topology A pointer to the topology containing the path nodes to be logged.
     * @param logs_path The path to the output log file.
     */
    static void logPathNodes(Topology* topology, const std::string& logs_path);

    /**
     * @brief Logs information about a single path node and its related path.
     *
     * This function logs information about a specific path node along with the sequence of element IDs in the
     * 'path_deque' to an output log stream provided by 'log_stream'.
     *
     * @param path_node A pointer to the path node to be logged.
     * @param path_deque A deque containing the sequence of element IDs in the path.
     * @param log_stream The output log stream to write the information to.
     */
    static void logPathNode(PathNode* path_node, std::deque<long>& path_deque, std::ofstream& log_stream);
};

#endif //SCHEDULING_PATHNODEUTILS_H

