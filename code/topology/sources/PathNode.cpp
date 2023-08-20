//
// Created by mihael on 8/15/23.
//

/**
 * @file PathNode.cpp
 * @brief Implements the member functions of the PathNode class.
 */

#include "PathNode.h"

PathNode::PathNode(TopologyElement *topology_element) {
    this->topology_element = topology_element;
}

PathNode::~PathNode() = default;

TopologyElement *PathNode::getTopologyElement() {
    return topology_element;
}