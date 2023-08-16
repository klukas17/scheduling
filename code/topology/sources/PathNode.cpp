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
    this->topology_element_type = ABSTRACT_TOPOLOGY_ELEMENT;
    this->general_topology_element_type = ABSTRACT_GENERAL_TOPOLOGY_ELEMENT;
}

TopologyElement *PathNode::getTopologyElement() {
    return topology_element;
}

TopologyElementType PathNode::getTopologyElementType() {
    return topology_element_type;
}

GeneralTopologyElementType PathNode::getGeneralTopologyElementType() {
    return general_topology_element_type;
}

PathNode::~PathNode() = default;