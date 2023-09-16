//
// Created by mihael on 8/20/23.
//

/**
 * @file GroupPathNode.cpp
 * @brief Implements the member functions of the GroupPathNode class.
 */

#include "GroupPathNode.h"

GroupPathNode::GroupPathNode(long path_node_id, TopologyElement* topology_element) : PathNode(path_node_id, topology_element) {}

GroupPathNode::~GroupPathNode() = default;