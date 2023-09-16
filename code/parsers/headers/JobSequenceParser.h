//
// Created by mihael on 29/04/23.
//

/**
 * @file JobSequenceParser.h
 * @brief Defines the JobSequenceParser class for parsing job sequences from a file.
 */

#ifndef SCHEDULING_JOBSEQUENCEPARSER_H
#define SCHEDULING_JOBSEQUENCEPARSER_H

#include <string>
#include <map>
#include "JobType.h"
#include "Job.h"
#include "JobTypeMap.h"
#include "Topology.h"
#include "TopologyElement.h"
#include "PathNode.h"
#include "yaml-cpp/yaml.h"
#include "MachineTypeMap.h"

/**
 * @class JobSequenceParser
 * @brief Provides functionality for parsing job sequences from files.
 *
 * The JobSequenceParser class offers a set of static functions for parsing job sequences from YAML files.
 * It can create Job objects, connect PathNodes, and calculate job processing times based on topology information.
 */
class JobSequenceParser {
public:
    /**
     * @brief Parses job sequences from the specified file.
     *
     * This function reads a YAML file containing job sequences, constructs Job objects, and returns them
     * in a map indexed by job IDs.
     *
     * @param path The path to the YAML file containing job sequences.
     * @param machine_type_map A pointer to the MachineTypeMap used for job parsing.
     * @param job_type_map A pointer to the JobTypeMap used for job parsing.
     * @param topology A pointer to the Topology object used for job parsing.
     * @return A map of job IDs to Job objects representing the parsed jobs.
     */
    static std::map<long, Job*> parse(const std::string& path, MachineTypeMap* machine_type_map, JobTypeMap* job_type_map, Topology* topology);

    /**
     * @brief Parses a PathNode using information from a YAML Node.
     *
     * This function parses a PathNode using information from a YAML Node and returns a pointer to the constructed PathNode.
     *
     * @param node The YAML Node containing information for constructing the PathNode.
     * @param path The path to the YAML file containing job sequences.
     * @param legal_topology_elements A map of legal topology elements for job path construction.
     * @param machine_type_map A pointer to the MachineTypeMap used for job parsing.
     * @param forbidden_machine_types A set of machine type IDs that are forbidden for job path construction.
     * @param path_tree_node_id The identifier for the associated path tree node.
     * @return A tuple containing the constructed PathNode, PathTreeNode, and the assigned path tree node ID.
     */
    static std::tuple<PathNode*, PathTreeNode*, long> parsePathNodeWithYAMLNode(const YAML::Node& node, const std::string& path, std::map<long, TopologyElement*> legal_topology_elements, MachineTypeMap* machine_type_map, const std::set<long>& forbidden_machine_types, long path_tree_node_id);

    /**
     * @brief Parses a PathNode without using YAML information.
     *
     * This function constructs a PathNode using information from provided parameters, without relying on YAML data.
     *
     * @param path The path to the YAML file containing job sequences.
     * @param topology_element A pointer to the associated topology element.
     * @param machine_type_map A pointer to the MachineTypeMap used for job parsing.
     * @param forbidden_machine_types A set of machine type IDs that are forbidden for job path construction.
     * @param path_tree_node_id The identifier for the associated path tree node.
     * @return A tuple containing the constructed PathNode, PathTreeNode, and the assigned path tree node ID.
     */
    static std::tuple<PathNode*, PathTreeNode*, long> parsePathNodeWithoutYAMLNode(const std::string& path, TopologyElement* topology_element, MachineTypeMap* machine_type_map, const std::set<long>& forbidden_machine_types, long path_tree_node_id);

    /**
     * @brief Connects two graphs of PathNodes to form a directed graph.
     *
     * This function connects two graphs of PathNodes to form a directed graph. It connects the last node
     * of the first graph to the first node of the second graph, effectively extending the sequence graph.
     *
     * @param path_node The last PathNode of the first graph.
     * @param next_path_node The first PathNode of the second graph.
     */
    static void connectGraphsOfPathNodes(PathNode* path_node, PathNode* next_path_node);

    /**
     * @brief Calculates job processing times based on the provided topology.
     *
     * This function calculates and assigns processing times for a Job object based on the provided Topology object.
     *
     * @param job A pointer to the Job for which processing times will be calculated.
     * @param topology A pointer to the Topology object used for processing time calculation.
     */
    static void calculateJobProcessingTimes(Job* job, Topology* topology);
};

#endif //SCHEDULING_JOBSEQUENCEPARSER_H
