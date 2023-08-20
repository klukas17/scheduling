//
// Created by mihael on 8/20/23.
//

/**
 * @file MachineJobPathNode.cpp
 * @brief Implements the member functions of the MachineJobPathNode class.
 */

#include "MachineJobPathNode.h"

MachineJobPathNode::MachineJobPathNode(PathNode *path_node) : JobPathNode(path_node) {
    this->next = nullptr;
}

JobPathNode *MachineJobPathNode::getNext() {
    return next;
}

void MachineJobPathNode::setNext(JobPathNode *job_path_node) {
    this->next = job_path_node;
}