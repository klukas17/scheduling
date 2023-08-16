//
// Created by mihael on 8/15/23.
//

/**
 * @file GroupPathNode.cpp
 * @brief Implements the member functions of the GroupPathNode class.
 */

#include "GroupPathNode.h"

GroupPathNode::GroupPathNode(TopologyElement *topology_element) : PathNode(topology_element) {
    this->general_topology_element_type = GROUP_GENERAL_TOPOLOGY_ELEMENT;
}

GroupPathNode::~GroupPathNode() = default;