//
// Created by mihael on 8/19/23.
//

/**
 * @file JobPathNodeUtils.cpp
 * @brief Implements the member functions of the JobPathNodeUtils class.
 */

#include "JobPathNodeUtils.h"
#include "SchedulingError.h"
#include "MachineJobPathNode.h"
#include "SerialGroupJobPathNode.h"
#include "ParallelGroupJobPathNode.h"
#include "RouteGroupJobPathNode.h"
#include "OpenGroupJobPathNode.h"
#include "iostream"

void JobPathNodeUtils::logJobPathNodes(std::map<long, Job*> jobs, const std::string &logs_path) {
    std::ofstream log_stream(logs_path);
    for (auto & job_pair : jobs) {
        log_stream << "JOB " << job_pair.first << ":" << std::endl;
        std::deque<long> job_path_nodes_deque;
        JobPathNodeUtils::logJobPathNode(job_pair.second->getPathsRootNode(), job_path_nodes_deque, log_stream);
        log_stream << std::endl;
    }
    log_stream.close();
}

void JobPathNodeUtils::logJobPathNode(JobPathNode *job_path_node, std::deque<long>& job_path_deque, std::ofstream & log_stream) {

    if (!job_path_node) {
        for (auto & node : job_path_deque) {
            log_stream << node << " ";
        }
        log_stream << std::endl;
        return;
    }

    auto path_node_topology_element_type = job_path_node->getPathNode()->getTopologyElement()->getTopologyElementType();
    long path_node_id = job_path_node->getPathNode()->getTopologyElement()->getId();

    if (path_node_topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Abstract topology element encountered in JobPathNodeUtils::logJobPathNode function.");
    }

    else if (path_node_topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        job_path_deque.push_back(path_node_id);
        logJobPathNode(((MachineJobPathNode *) job_path_node)->getNext(), job_path_deque, log_stream);
        job_path_deque.pop_back();
    }

    else if (path_node_topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        job_path_deque.push_back(path_node_id);
        logJobPathNode(((SerialGroupJobPathNode *) job_path_node)->getNext(), job_path_deque, log_stream);
        job_path_deque.pop_back();
    }

    else if (path_node_topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        job_path_deque.push_back(path_node_id);
        for (auto & child : ((ParallelGroupJobPathNode*)job_path_node)->getNext()) {
            logJobPathNode(child.second, job_path_deque, log_stream);
        }
        job_path_deque.pop_back();
    }

    else if (path_node_topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        job_path_deque.push_back(path_node_id);
        logJobPathNode(((RouteGroupJobPathNode *) job_path_node)->getNext(), job_path_deque, log_stream);
        job_path_deque.pop_back();
    }

    else if (path_node_topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        for (auto job_sub_path_node : ((OpenGroupJobPathNode*)job_path_node)->getJobSubPathNodes()) {
            std::deque<long> sub_path_node_deque = {path_node_id};
            logJobPathNode(job_sub_path_node.second, sub_path_node_deque, log_stream);
        }
        job_path_deque.push_back(path_node_id);
        logJobPathNode(((OpenGroupJobPathNode *) job_path_node)->getNext(), job_path_deque, log_stream);
        job_path_deque.pop_back();
    }
}