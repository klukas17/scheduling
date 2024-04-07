//
// Created by mihael on 9/3/23.
//

#include "PathTreeNode.h"
#include "SchedulingError.h"
#include "GroupPathTreeNode.h"

PathTreeNode::PathTreeNode(PathNode *path_node) {
    this->path_node = path_node;
}

PathTreeNode::~PathTreeNode() = default;

PathNode *PathTreeNode::getPathNode() const {
    return path_node;
}

void PathTreeNode::deletePathTreeNode() {

    auto const general_topology_element_type = path_node->getTopologyElement()->getGeneralTopologyElementType();

    if (general_topology_element_type == ABSTRACT_GENERAL_TOPOLOGY_ELEMENT) {
        throw SchedulingError("Trying to delete an abstract topology element.");
    }

    if (general_topology_element_type == MACHINE_GENERAL_TOPOLOGY_ELEMENT) {
        delete this;
    }

    else if (general_topology_element_type == GROUP_GENERAL_TOPOLOGY_ELEMENT) {
        for (auto const child : dynamic_cast<GroupPathTreeNode*>(this)->getChildren()) {
            child->deletePathTreeNode();
        }
        delete this;
    }
}