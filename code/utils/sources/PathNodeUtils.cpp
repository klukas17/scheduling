//
// Created by mihael on 8/19/23.
//

#include "PathNodeUtils.h"
#include "SchedulingError.h"
#include "MachinePathNode.h"
#include "SerialGroupPathNode.h"
#include "ParallelGroupPathNode.h"
#include "RouteGroupPathNode.h"
#include "OpenGroupPathNode.h"
#include "fstream"

void PathNodeUtils::logPathNodes(const std::map<long, Job*>& jobs, const std::string &logs_path) {
    std::ofstream log_stream(logs_path);
    for (auto [job_id, job] : jobs) {
        log_stream << "JOB " << job_id << ":" << std::endl;
        std::deque<long> path_node_deque;
        logPathNode(job->getPathsRootNode(), path_node_deque, log_stream);
        log_stream << std::endl;
    }
    log_stream.close();
}

void PathNodeUtils::logPathNode(PathNode *path_node, std::deque<long>& path_node_deque, std::ofstream & log_stream) {

    if (!path_node) {
        for (auto const & node : path_node_deque) {
            log_stream << node << " ";
        }
        log_stream << std::endl;
        return;
    }

    auto const path_node_topology_element_type = path_node->getTopologyElement()->getTopologyElementType();
    long const path_node_id = path_node->getTopologyElement()->getId();

    if (path_node_topology_element_type == ABSTRACT_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Abstract topology element encountered in PathNodeUtils::logPathNode function.");
    }

    if (path_node_topology_element_type == MACHINE_TOPOLOGY_ELEMENT) {
        path_node_deque.push_back(path_node_id);
        logPathNode(dynamic_cast<MachinePathNode*>(path_node)->getNext(), path_node_deque, log_stream);
        path_node_deque.pop_back();
    }

    else if (path_node_topology_element_type == SERIAL_GROUP_TOPOLOGY_ELEMENT) {
        path_node_deque.push_back(path_node_id);
        logPathNode(dynamic_cast<SerialGroupPathNode*>(path_node)->getNext(), path_node_deque, log_stream);
        path_node_deque.pop_back();
    }

    else if (path_node_topology_element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        path_node_deque.push_back(path_node_id);
        for (auto const [_, child] : dynamic_cast<ParallelGroupPathNode*>(path_node)->getNext()) {
            logPathNode(child, path_node_deque, log_stream);
        }
        path_node_deque.pop_back();
    }

    else if (path_node_topology_element_type == ROUTE_GROUP_TOPOLOGY_ELEMENT) {
        path_node_deque.push_back(path_node_id);
        logPathNode(dynamic_cast<RouteGroupPathNode*>(path_node)->getNext(), path_node_deque, log_stream);
        path_node_deque.pop_back();
    }

    else if (path_node_topology_element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
        for (auto const [_, child] : dynamic_cast<OpenGroupPathNode*>(path_node)->getSubPathNodes()) {
            std::deque sub_path_node_deque = {path_node_id};
            logPathNode(child, sub_path_node_deque, log_stream);
        }
        path_node_deque.push_back(path_node_id);
        logPathNode(dynamic_cast<OpenGroupPathNode*>(path_node)->getNext(), path_node_deque, log_stream);
        path_node_deque.pop_back();
    }
}