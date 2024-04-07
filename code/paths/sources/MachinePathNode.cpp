//
// Created by mihael on 8/20/23.
//

#include "MachinePathNode.h"

MachinePathNode::MachinePathNode(long const path_node_id, TopologyElement* topology_element) : PathNode(path_node_id, topology_element) {
    this->next = nullptr;
}

PathNode *MachinePathNode::getNext() const {
    return next;
}

void MachinePathNode::setNext(PathNode *path_node) {
    this->next = path_node;
}