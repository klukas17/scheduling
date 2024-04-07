//
// Created by mihael on 8/20/23.
//

#include "ParallelGroupPathNode.h"
#include "map"

ParallelGroupPathNode::ParallelGroupPathNode(long const path_node_id, TopologyElement* topology_element) : GroupPathNode(path_node_id, topology_element) {}

std::map<long, PathNode *> ParallelGroupPathNode::getNext() {
    return next;
}

void ParallelGroupPathNode::setNext(long const id, PathNode *path_node) {
    this->next[id] = path_node;
}