//
// Created by mihael on 9/14/23.
//

#include "JobProcessingContextFrame.h"
#include "SchedulingError.h"
#include "algorithm"

JobProcessingContextFrame::JobProcessingContextFrame(OpenGroupPathTreeNode *open_group_path_tree_node) {
    this->open_group_path_tree_node = open_group_path_tree_node;
    for (auto const child : open_group_path_tree_node->getChildren()) {
        children_visited[child->getPathNode()->getPathNodeId()] = false;
    }
}

OpenGroupPathTreeNode *JobProcessingContextFrame::getOpenGroupPathTreeNode() const {
    return open_group_path_tree_node;
}

void JobProcessingContextFrame::visitChild(long const path_node_id) {
    if (children_visited[path_node_id]) {
        throw SchedulingError("Child with path_node_id " + std::to_string(path_node_id) + " already visited in JobProcessingContextFrame::visitChild function");
    }
    children_visited[path_node_id] = true;
}

bool JobProcessingContextFrame::checkAllChildrenVisited() {
    if (!std::ranges::all_of(children_visited, [](const auto& entry) { return entry.second; })) {
        return false;
    }
    return true;
}