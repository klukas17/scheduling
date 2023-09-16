//
// Created by mihael on 8/20/23.
//

/**
 * @file SerialGroupPathNode.cpp
 * @brief Implements the member functions of the SerialGroupPathNode class.
 */

#include "SerialGroupPathNode.h"

SerialGroupPathNode::SerialGroupPathNode(long path_node_id, TopologyElement* topology_element) : GroupPathNode(path_node_id, topology_element) {
    this->next = nullptr;
}

PathNode *SerialGroupPathNode::getNext() {
    return next;
}

void SerialGroupPathNode::setNext(PathNode *path_node) {
    this->next = path_node;
}