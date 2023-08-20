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
#include "PathNode.h"
#include "yaml-cpp/yaml.h"

/**
 * @class JobSequenceParser
 * @brief Parses job sequences from a file.
 *
 * The JobSequenceParser class is responsible for reading job sequences from a file and constructing a map of all jobs.
 */
class JobSequenceParser {
public:
    /**
     * @brief Parses job sequences from the specified file..
     *
     * This function reads a YAML file containing job sequences and constructs a map of all jobs.
     *
     * @param path The path to the YAML file containing job sequences.
     * @param job_type_map A map of job IDs to JobType pointers.
     * @param topology The topology object.
     * @return A map of job IDs to Job pointers representing the constructed Job objects.
     */
    static std::map<long, Job*> parse(const std::string& path, JobTypeMap* job_type_map, Topology* topology);

    /**
     * @brief Parses a JobPathNode using information from a YAML Node.
     *
     * This function parses a JobPathNode using information from a YAML Node.
     *
     * @param node The YAML Node containing information about the JobPathNode.
     * @param path The path to the YAML file.
     * @param legal_path_nodes A map of legal path node IDs to PathNode pointers.
     * @return A pointer to the constructed JobPathNode.
     */
    static JobPathNode* parsePathNodeWithYAMLNode(const YAML::Node& node, const std::string& path, std::map<long, PathNode*> legal_path_nodes);

    /**
     * @brief Parses a JobPathNode without using YAML information.
     *
     * This function constructs a JobPathNode using information from provided parameters, without relying on YAML data,
     * using default rules for each topology element type.
     *
     * @param path The path to the YAML file.
     * @param path_node The existing PathNode to which the constructed JobPathNode will be connected.
     * @return A pointer to the constructed JobPathNode.
     */
    static JobPathNode* parsePathNodeWithoutYAMLNode(const std::string& path, PathNode* path_node);

    /**
     * @brief Connects two graphs of JobPathNodes to form a directed graph.
     *
     * This function connects two graphs of JobPathNodes to form a directed graph. It connects the last node
     * of the first graph to the first node of the second graph, effectively extending the sequence graph.
     *
     * @param job_path_node The last JobPathNode of the first graph.
     * @param next_job_path_node The first JobPathNode of the second graph.
     */
    static void connectGraphsOfJobPathNodes(JobPathNode* job_path_node, JobPathNode* next_job_path_node);
};

#endif //SCHEDULING_JOBSEQUENCEPARSER_H
