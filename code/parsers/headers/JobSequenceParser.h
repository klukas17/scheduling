//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_JOBSEQUENCEPARSER_H
#define SCHEDULING_JOBSEQUENCEPARSER_H

#include <string>
#include <map>
#include "Job.h"
#include "JobTypeMap.h"
#include "Topology.h"
#include "TopologyElement.h"
#include "PathNode.h"
#include "yaml-cpp/yaml.h"
#include "MachineTypeMap.h"

class JobSequenceParser {
public:
    static std::map<long, Job*> parse(const std::string& path, MachineTypeMap* machine_type_map, JobTypeMap* job_type_map, Topology* topology);
    static std::tuple<PathNode*, PathTreeNode*, long> parsePathNodeWithYAMLNode(const YAML::Node& node, const std::string& path, std::map<long, TopologyElement*> legal_topology_elements, MachineTypeMap* machine_type_map, const std::set<long>& forbidden_machine_types, long path_tree_node_id);
    static std::tuple<PathNode*, PathTreeNode*, long> parsePathNodeWithoutYAMLNode(const std::string& path, TopologyElement* topology_element, MachineTypeMap* machine_type_map, const std::set<long>& forbidden_machine_types, long path_tree_node_id);
    static void connectGraphsOfPathNodes(PathNode* path_node, PathNode* next_path_node);
    static void calculateJobProcessingTimes(Job* job, Topology* topology);
    static void calculatePredecessors(Job* job, PathNode* path_node);
    static void calculateRemainingProcessingTimes(Job* job, PathNode* path_node);
};

#endif //SCHEDULING_JOBSEQUENCEPARSER_H
