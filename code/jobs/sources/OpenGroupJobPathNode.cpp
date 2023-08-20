//
// Created by mihael on 8/20/23.
//

/**
 * @file OpenGroupJobPathNode.cpp
 * @brief Implements the member functions of the OpenGroupJobPathNode class.
 */

#include "OpenGroupJobPathNode.h"

OpenGroupJobPathNode::OpenGroupJobPathNode(PathNode *path_node) : GroupJobPathNode(path_node) {
    this->next = nullptr;
}

JobPathNode *OpenGroupJobPathNode::getNext() {
    return next;
}

void OpenGroupJobPathNode::setNext(JobPathNode *job_path_node) {
    this->next = job_path_node;
}

std::map<long, JobPathNode *> OpenGroupJobPathNode::getJobSubPathNodes() {
    return job_sub_path_nodes;
}

void OpenGroupJobPathNode::addJobSubPathNode(long id, JobPathNode *job_path_node) {
    this->job_sub_path_nodes[id] = job_path_node;
}