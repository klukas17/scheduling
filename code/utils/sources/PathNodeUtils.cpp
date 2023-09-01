//
// Created by mihael on 8/19/23.
//

/**
 * @file PathNodeUtils.cpp
 * @brief Implements the member functions of the PathNodeUtils class.
 */

#include "PathNodeUtils.h"
#include "SchedulingError.h"
#include "MachinePathNode.h"
#include "SerialGroupPathNode.h"
#include "ParallelGroupPathNode.h"
#include "RouteGroupPathNode.h"
#include "OpenGroupPathNode.h"
#include "iostream"

void PathNodeUtils::logPathNodes(std::map<long, Job*> jobs, const std::string &logs_path) {
    std::ofstream log_stream(logs_path);
    for (auto & job_pair : jobs) {
        log_stream << "JOB " << job_pair.first << ":" << std::endl;
        std::deque<long> path_node_deque;
        PathNodeUtils::logPathNode(job_pair.second->getPathsRootNode(), path_node_deque, log_stream);
        log_stream << std::endl;
    }
    log_stream.close();
}

void PathNodeUtils::logPathNode(PathNode *path_node, std::deque<long>& path_node_deque, std::ofstream & log_stream) {

    if (!path_node) {
        for (auto & node : path_node_deque) {
            log_stream << node << " ";
        }
        log_stream << std::endl;
        return;
    }

    auto path_node_topology_element_type = path_node->getTopologyElement()->getTopologyElementType();
    long path_node_id = path_node->getTopologyElement()->getId();

    if (path_node_topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Abstract topology element encountered in PathNodeUtils::logPathNode function.");
    }

    else if (path_node_topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        path_node_deque.push_back(path_node_id);
        logPathNode(((MachinePathNode *) path_node)->getNext(), path_node_deque, log_stream);
        path_node_deque.pop_back();
    }

    else if (path_node_topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        path_node_deque.push_back(path_node_id);
        logPathNode(((SerialGroupPathNode *) path_node)->getNext(), path_node_deque, log_stream);
        path_node_deque.pop_back();
    }

    else if (path_node_topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        path_node_deque.push_back(path_node_id);
        for (auto & child : ((ParallelGroupPathNode*) path_node)->getNext()) {
            logPathNode(child.second, path_node_deque, log_stream);
        }
        path_node_deque.pop_back();
    }

    else if (path_node_topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        path_node_deque.push_back(path_node_id);
        logPathNode(((RouteGroupPathNode *) path_node)->getNext(), path_node_deque, log_stream);
        path_node_deque.pop_back();
    }

    else if (path_node_topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        for (auto sub_path_node : ((OpenGroupPathNode *) path_node)->getSubPathNodes()) {
            std::deque<long> sub_path_node_deque = {path_node_id};
            logPathNode(sub_path_node.second, sub_path_node_deque, log_stream);
        }
        path_node_deque.push_back(path_node_id);
        logPathNode(((OpenGroupPathNode *) path_node)->getNext(), path_node_deque, log_stream);
        path_node_deque.pop_back();
    }
}