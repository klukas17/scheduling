//
// Created by mihael on 29/06/23.
//

/**
 * @file JobPathNode.cpp
 * @brief Implements the member functions of the JobPathNode class.
 */

#include "JobPathNode.h"

JobPathNode::JobPathNode(PathNode *path_node) {
    this->path_node = path_node;
}

JobPathNode::~JobPathNode() = default;

PathNode *JobPathNode::getPathNode() {
    return path_node;
}

std::vector<Prerequisite *> JobPathNode::getPrerequisites() {
    return prerequisites;
}

void JobPathNode::addPrerequisite(Prerequisite *prerequisite) {
    prerequisites.push_back(prerequisite);
}