//
// Created by mihael on 8/20/23.
//

/**
 * @file ParallelGroupJobPathNode.cpp
 * @brief Implements the member functions of the ParallelGroupJobPathNode class.
 */

#include "ParallelGroupJobPathNode.h"

ParallelGroupJobPathNode::ParallelGroupJobPathNode(PathNode* path_node) : GroupJobPathNode(path_node) {}

std::map<long, JobPathNode *> ParallelGroupJobPathNode::getNext() {
    return next;
}

void ParallelGroupJobPathNode::setNext(long id, JobPathNode *job_path_node) {
    this->next[id] = job_path_node;
}