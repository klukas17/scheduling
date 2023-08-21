//
// Created by mihael on 01/05/23.
//

/**
 * @file ParallelGroupNode.cpp
 * @brief Implements the member functions of the ParallelGroupNode class.
 */

#include "ParallelGroupNode.h"

ParallelGroupNode::ParallelGroupNode(long id) : GroupNode(id) {
    this->node_type = PARALLEL_GROUP_NODE;
}