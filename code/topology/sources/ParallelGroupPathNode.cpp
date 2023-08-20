//
// Created by mihael on 8/15/23.
//

/**
 * @file ParallelGroupPathNode.cpp
 * @brief Implements the member functions of the ParallelGroupPathNode class.
 */

#include "ParallelGroupPathNode.h"

ParallelGroupPathNode::ParallelGroupPathNode(TopologyElement *topology_element) : GroupPathNode(topology_element) {}

std::map<long, PathNode *> ParallelGroupPathNode::getNext() {
    return next;
}

void ParallelGroupPathNode::addNext(long id, PathNode *next) {
    this->next[id] = next;
}