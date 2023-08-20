//
// Created by mihael on 8/20/23.
//

/**
 * @file SerialGroupJobPathNode.cpp
 * @brief Implements the member functions of the SerialGroupJobPathNode class.
 */

#include "SerialGroupJobPathNode.h"

SerialGroupJobPathNode::SerialGroupJobPathNode(PathNode* path_node) : GroupJobPathNode(path_node) {
    this->next = nullptr;
}

JobPathNode *SerialGroupJobPathNode::getNext() {
    return next;
}

void SerialGroupJobPathNode::setNext(JobPathNode *job_path_node) {
    this->next = job_path_node;
}