//
// Created by mihael on 9/14/23.
//

/**
 * @file JobProcessingContextFrame.cpp
 * @brief Implements the member functions of the JobProcessingContextFrame class.
 */

#include "JobProcessingContextFrame.h"
#include "SchedulingError.h"

JobProcessingContextFrame::JobProcessingContextFrame(OpenGroupPathTreeNode *open_group_path_tree_node) {
    this->open_group_path_tree_node = open_group_path_tree_node;
    for (auto child : open_group_path_tree_node->getChildren()) {
        children_visited[child->getPathNode()->getPathNodeId()] = false;
    }
}

OpenGroupPathTreeNode *JobProcessingContextFrame::getOpenGroupPathTreeNode() {
    return open_group_path_tree_node;
}

void JobProcessingContextFrame::visitChild(long path_node_id) {
    if (children_visited[path_node_id]) {
        throw SchedulingError("Child with path_node_id " + std::to_string(path_node_id) + " already visited in JobProcessingContextFrame::visitChild function");
    }
    children_visited[path_node_id] = true;
}

bool JobProcessingContextFrame::checkAllChildrenVisited() {
    for (auto &entry : children_visited) {
        if (!children_visited[entry.first]) {
            return false;
        }
    }
    return true;
}