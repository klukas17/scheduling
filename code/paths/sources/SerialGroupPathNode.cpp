//
// Created by mihael on 8/20/23.
//

#include "SerialGroupPathNode.h"

SerialGroupPathNode::SerialGroupPathNode(long const path_node_id, TopologyElement* topology_element) : GroupPathNode(path_node_id, topology_element) {
    this->next = nullptr;
}

PathNode *SerialGroupPathNode::getNext() const {
    return next;
}

void SerialGroupPathNode::setNext(PathNode *path_node) {
    this->next = path_node;
}