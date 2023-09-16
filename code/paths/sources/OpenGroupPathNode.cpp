//
// Created by mihael on 8/20/23.
//

/**
 * @file OpenGroupPathNode.cpp
 * @brief Implements the member functions of the OpenGroupPathNode class.
 */

#include "OpenGroupPathNode.h"

OpenGroupPathNode::OpenGroupPathNode(long path_node_id, TopologyElement* topology_element) : GroupPathNode(path_node_id, topology_element) {
    this->next = nullptr;
}

PathNode *OpenGroupPathNode::getNext() {
    return next;
}

void OpenGroupPathNode::setNext(PathNode *job_path_node) {
    this->next = job_path_node;
}

std::vector<std::pair<long, PathNode*>> OpenGroupPathNode::getSubPathNodes() {
    return sub_path_nodes;
}

void OpenGroupPathNode::addSubPathNode(long id, PathNode *path_node) {
    this->sub_path_nodes.emplace_back(id, path_node);
}