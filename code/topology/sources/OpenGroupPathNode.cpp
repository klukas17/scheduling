//
// Created by mihael on 8/15/23.
//

/**
 * @file OpenGroupPathNode.cpp
 * @brief Implements the member functions of the OpenGroupPathNode class.
 */

#include "OpenGroupPathNode.h"

OpenGroupPathNode::OpenGroupPathNode(TopologyElement *topology_element) : GroupPathNode(topology_element) {
    this->next = nullptr;
}

PathNode *OpenGroupPathNode::getNext() {
    return next;
}

void OpenGroupPathNode::setNext(PathNode *next) {
    this->next = next;
}

std::vector<PathNode *> OpenGroupPathNode::getSubPathNodes() {
    return sub_path_nodes;
}

void OpenGroupPathNode::addSubPathNode(PathNode *sub_path_node) {
    sub_path_nodes.push_back(sub_path_node);
}