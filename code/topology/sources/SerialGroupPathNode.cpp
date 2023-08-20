//
// Created by mihael on 8/15/23.
//

/**
 * @file SerialGroupPathNode.cpp
 * @brief Implements the member functions of the SerialGroupPathNode class.
 */

#include "SerialGroupPathNode.h"

SerialGroupPathNode::SerialGroupPathNode(TopologyElement *topology_element) : GroupPathNode(topology_element) {
    this->next = nullptr;
}

PathNode *SerialGroupPathNode::getNext() {
    return next;
}

void SerialGroupPathNode::setNext(PathNode *next) {
    this->next = next;
}

std::vector<PathNode *> SerialGroupPathNode::getChildren() {
    return children;
}

void SerialGroupPathNode::addChild(PathNode *path_node) {
    children.push_back(path_node);
}