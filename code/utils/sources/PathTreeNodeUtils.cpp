//
// Created by mihael on 9/3/23.
//

#include "PathTreeNodeUtils.h"
#include "SchedulingError.h"
#include "MachinePathTreeNode.h"
#include "GroupPathTreeNode.h"
#include "fstream"

void PathTreeNodeUtils::logPathTreeNodes(std::map<long, Job *>& jobs, const std::string &logs_path) {
    std::ofstream log_stream(logs_path);
    for (auto [job_id, job] : jobs) {
        log_stream << "JOB " << job_id << ":" << std::endl;
        logPathTreeNode(job->getPathsRootTreeNode(), 0, log_stream);
        log_stream << std::endl;
    }
    log_stream.close();
}

void PathTreeNodeUtils::logPathTreeNode(PathTreeNode *path_tree_node, int const indents, std::ofstream &log_stream) {

    for (int i = 0; i < indents; i++) {
        log_stream << "\t";
    }

    switch(path_tree_node->getPathNode()->getTopologyElement()->getTopologyElementType()) {

        case ABSTRACT_TOPOLOGY_ELEMENT:
            throw SchedulingError("Abstract topology element encountered in PathTreeNodeUtils::logPathTreeNode function.");

        case MACHINE_TOPOLOGY_ELEMENT:
            log_stream << "Machine: " << "id = " << path_tree_node->getPathNode()->getTopologyElement()->getId()
                       << ", path_node_id = " << path_tree_node->getPathNode()->getPathNodeId() << std::endl;
            break;

        case SERIAL_GROUP_TOPOLOGY_ELEMENT:
            log_stream << "Serial group: " << "id = " << path_tree_node->getPathNode()->getTopologyElement()->getId()
                       << ", path_node_id = " << path_tree_node->getPathNode()->getPathNodeId() << std::endl;
            for (auto const child : dynamic_cast<GroupPathTreeNode*>(path_tree_node)->getChildren()) {
                logPathTreeNode(child, indents + 1, log_stream);
            }
            break;

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
            log_stream << "Parallel group: " << "id = " << path_tree_node->getPathNode()->getTopologyElement()->getId()
                       << ", path_node_id = " << path_tree_node->getPathNode()->getPathNodeId() << std::endl;
            for (auto const child : dynamic_cast<GroupPathTreeNode*>(path_tree_node)->getChildren()) {
                logPathTreeNode(child, indents + 1, log_stream);
            }
            break;

        case ROUTE_GROUP_TOPOLOGY_ELEMENT:
            log_stream << "Route group: " << "id = " << path_tree_node->getPathNode()->getTopologyElement()->getId()
                       << ", path_node_id = " << path_tree_node->getPathNode()->getPathNodeId() << std::endl;
            for (auto const child : dynamic_cast<GroupPathTreeNode*>(path_tree_node)->getChildren()) {
                logPathTreeNode(child, indents + 1, log_stream);
            }
            break;

        case OPEN_GROUP_TOPOLOGY_ELEMENT:
            log_stream << "Open group: " << "id = " << path_tree_node->getPathNode()->getTopologyElement()->getId()
                       << ", path_node_id = " << path_tree_node->getPathNode()->getPathNodeId() << std::endl;
            for (auto const child : dynamic_cast<GroupPathTreeNode*>(path_tree_node)->getChildren()) {
                logPathTreeNode(child, indents + 1, log_stream);
            }
            break;
    }
}