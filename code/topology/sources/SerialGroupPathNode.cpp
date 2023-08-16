//
// Created by mihael on 8/15/23.
//

/**
 * @file SerialGroupPathNode.cpp
 * @brief Implements the member functions of the SerialGroupPathNode class.
 */

#include "SerialGroupPathNode.h"

SerialGroupPathNode::SerialGroupPathNode(TopologyElement *topology_element) : GroupPathNode(topology_element) {
    this->topology_element_type = SERIAL_GROUP_TOPOLOGY_ELEMENT;
    this->next = nullptr;
}

PathNode *SerialGroupPathNode::getNext() {
    return next;
}

void SerialGroupPathNode::setNext(PathNode *next) {
    this->next = next;
}