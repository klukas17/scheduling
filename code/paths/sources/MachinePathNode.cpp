//
// Created by mihael on 8/20/23.
//

/**
 * @file MachinePathNode.cpp
 * @brief Implements the member functions of the MachinePathNode class.
 */

#include "MachinePathNode.h"

MachinePathNode::MachinePathNode(long path_node_id, TopologyElement* topology_element) : PathNode(path_node_id, topology_element) {
    this->next = nullptr;
}

PathNode *MachinePathNode::getNext() {
    return next;
}

void MachinePathNode::setNext(PathNode *path_node) {
    this->next = path_node;
}