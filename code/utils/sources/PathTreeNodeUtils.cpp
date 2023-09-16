//
// Created by mihael on 9/3/23.
//

/**
 * @file PathTreeNodeUtils.cpp
 * @brief Implements the member functions of the PathTreeNodeUtils class.
 */

#include "PathTreeNodeUtils.h"
#include "SchedulingError.h"
#include "MachinePathTreeNode.h"
#include "SerialGroupPathTreeNode.h"
#include "ParallelGroupPathTreeNode.h"
#include "RouteGroupPathTreeNode.h"
#include "OpenGroupPathTreeNode.h"

void PathTreeNodeUtils::logPathTreeNodes(std::map<long, Job *> jobs, const std::string &logs_path) {
    std::ofstream log_stream(logs_path);
    for (auto & job_pair : jobs) {
        log_stream << "JOB " << job_pair.first << ":" << std::endl;
        PathTreeNodeUtils::logPathTreeNode(job_pair.second->getPathsRootTreeNode(), 0, log_stream);
        log_stream << std::endl;
    }
    log_stream.close();
}

void PathTreeNodeUtils::logPathTreeNode(PathTreeNode *path_tree_node, int indents, std::ofstream &log_stream) {

    for (int i = 0; i < indents; i++) {
        log_stream << "\t";
    }

    switch(path_tree_node->getPathNode()->getTopologyElement()->getTopologyElementType()) {

        case ABSTRACT_TOPOLOGY_ELEMENT:
            throw SchedulingError("Abstract topology element encountered in PathTreeNodeUtils::logPathTreeNode function.");

        case MACHINE_TOPOLOGY_ELEMENT:
            log_stream << "Machine: " << "id = " << ((MachinePathTreeNode*)path_tree_node)->getPathNode()->getTopologyElement()->getId()
                       << ", path_node_id = " << ((MachinePathTreeNode*)path_tree_node)->getPathNode()->getPathNodeId() << std::endl;
            break;

        case SERIAL_GROUP_TOPOLOGY_ELEMENT:
            log_stream << "Serial group: " << "id = " << ((SerialGroupPathTreeNode*)path_tree_node)->getPathNode()->getTopologyElement()->getId()
                       << ", path_node_id = " << ((SerialGroupPathTreeNode*)path_tree_node)->getPathNode()->getPathNodeId() << std::endl;
            for (auto child : ((GroupPathTreeNode*)path_tree_node)->getChildren()) {
                logPathTreeNode(child, indents + 1, log_stream);
            }
            break;

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
            log_stream << "Parallel group: " << "id = " << ((ParallelGroupPathTreeNode*)path_tree_node)->getPathNode()->getTopologyElement()->getId()
                       << ", path_node_id = " << ((ParallelGroupPathTreeNode*)path_tree_node)->getPathNode()->getPathNodeId() << std::endl;
            for (auto child : ((GroupPathTreeNode*)path_tree_node)->getChildren()) {
                logPathTreeNode(child, indents + 1, log_stream);
            }
            break;

        case ROUTE_GROUP_TOPOLOGY_ELEMENT:
            log_stream << "Route group: " << "id = " << ((RouteGroupPathTreeNode*)path_tree_node)->getPathNode()->getTopologyElement()->getId()
                       << ", path_node_id = " << ((RouteGroupPathTreeNode*)path_tree_node)->getPathNode()->getPathNodeId() << std::endl;
            for (auto child : ((GroupPathTreeNode*)path_tree_node)->getChildren()) {
                logPathTreeNode(child, indents + 1, log_stream);
            }
            break;

        case OPEN_GROUP_TOPOLOGY_ELEMENT:
            log_stream << "Open group: " << "id = " << ((OpenGroupPathTreeNode*)path_tree_node)->getPathNode()->getTopologyElement()->getId()
                       << ", path_node_id = " << ((OpenGroupPathTreeNode*)path_tree_node)->getPathNode()->getPathNodeId() << std::endl;
            for (auto child : ((GroupPathTreeNode*)path_tree_node)->getChildren()) {
                logPathTreeNode(child, indents + 1, log_stream);
            }
            break;
    }
}