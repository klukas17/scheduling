//
// Created by mihael on 8/15/23.
//

/**
 * @file ParallelGroupPathNode.cpp
 * @brief Implements the member functions of the ParallelGroupPathNode class.
 */

#include "ParallelGroupPathNode.h"

ParallelGroupPathNode::ParallelGroupPathNode(TopologyElement *topology_element) : GroupPathNode(topology_element) {
    this->topology_element_type = PARALLEL_GROUP_TOPOLOGY_ELEMENT;
}

std::vector<PathNode *> ParallelGroupPathNode::getNext() {
    return next;
}

void ParallelGroupPathNode::addNext(PathNode *next) {
    this->next.push_back(next);
}