//
// Created by mihael on 8/20/23.
//

/**
 * @file RouteGroupJobPathNode.cpp
 * @brief Implements the member functions of the RouteGroupJobPathNode class.
 */

#include "RouteGroupJobPathNode.h"

RouteGroupJobPathNode::RouteGroupJobPathNode(PathNode* path_node) : GroupJobPathNode(path_node) {
    this->next = nullptr;
}

JobPathNode *RouteGroupJobPathNode::getNext() {
    return next;
}

void RouteGroupJobPathNode::setNext(JobPathNode *job_path_node) {
    this->next = job_path_node;
}