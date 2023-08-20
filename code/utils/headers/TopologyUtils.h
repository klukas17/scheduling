//
// Created by mihael on 8/19/23.
//

/**
 * @file TopologyUtils.h
 * @brief Defines the TopologyUtils class for providing utility functions for logging topology elements and topologies.
 */

#ifndef SCHEDULING_TOPOLOGYUTILS_H
#define SCHEDULING_TOPOLOGYUTILS_H

#include "Topology.h"
#include "string"
#include "fstream"

/**
 * @class TopologyUtils
 * @brief Provides utility functions for logging topology elements and topologies.
 *
 * The TopologyUtils class offers static utility functions to assist in logging information about topology elements
 * and entire topologies, along with their corresponding details.
 */
class TopologyUtils {
public:
    /**
     * @brief Logs information about a topology to an output file.
     *
     * This function logs information about the provided topology to an output file specified by the 'logs_path'.
     * It logs details about topology elements and their relationships.
     *
     * @param topology A pointer to the topology to be logged.
     * @param logs_path The path to the output log file.
     */
    static void logTopology(Topology* topology, const std::string& logs_path);

    /**
     * @brief Logs information about a single topology element recursively.
     *
     * This function logs information about a specific topology element, including its children, in a recursive manner.
     * It uses the 'indents' parameter to control the level of indentation in the log output.
     *
     * @param topology_element A pointer to the topology element to be logged.
     * @param indents The number of indents to apply for proper formatting.
     * @param log_stream The output log stream to write the information to.
     */
    static void logTopologyElement(TopologyElement* topology_element, int indents, std::ofstream& log_stream);
};

#endif //SCHEDULING_TOPOLOGYUTILS_H

