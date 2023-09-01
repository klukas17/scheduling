//
// Created by mihael on 8/20/23.
//

/**
 * @file RouteGroupPathNode.cpp
 * @brief Implements the member functions of the RouteGroupPathNode class.
 */

#include "RouteGroupPathNode.h"

RouteGroupPathNode::RouteGroupPathNode(TopologyElement* topology_element) : GroupPathNode(topology_element) {
    this->next = nullptr;
}

PathNode *RouteGroupPathNode::getNext() {
    return next;
}

void RouteGroupPathNode::setNext(PathNode *path_node) {
    this->next = path_node;
}