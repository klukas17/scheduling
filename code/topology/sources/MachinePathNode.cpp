//
// Created by mihael on 8/15/23.
//

/**
 * @file MachinePathNode.cpp
 * @brief Implements the member functions of the MachinePathNode class.
 */

#include "MachinePathNode.h"

MachinePathNode::MachinePathNode(TopologyElement *topology_element) : PathNode(topology_element) {
    this->next = nullptr;
}

PathNode *MachinePathNode::getNext() {
    return next;
}

void MachinePathNode::setNext(PathNode *next) {
    this->next = next;
}