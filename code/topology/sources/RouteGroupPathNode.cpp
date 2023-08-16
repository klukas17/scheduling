//
// Created by mihael on 8/15/23.
//

/**
 * @file RouteGroupPathNode.cpp
 * @brief Implements the member functions of the RouteGroupPathNode class.
 */

#include "RouteGroupPathNode.h"

RouteGroupPathNode::RouteGroupPathNode(TopologyElement *topology_element) : GroupPathNode(topology_element) {
    this->topology_element_type = ROUTE_GROUP_TOPOLOGY_ELEMENT;
    this->next = nullptr;
}

PathNode *RouteGroupPathNode::getNext() {
    return next;
}

void RouteGroupPathNode::setNext(PathNode *next) {
    this->next = next;
}

std::vector<PathNode *> RouteGroupPathNode::getSubPathNodes() {
    return sub_path_nodes;
}

void RouteGroupPathNode::addSubPathNode(PathNode *sub_path_node) {
    sub_path_nodes.push_back(sub_path_node);
}