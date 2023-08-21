//
// Created by mihael on 01/05/23.
//

/**
 * @file OpenGroupNode.cpp
 * @brief Implements the member functions of the OpenGroupNode class.
 */

#include "OpenGroupNode.h"

OpenGroupNode::OpenGroupNode(long id) : GroupNode(id) {
    this->node_type = OPEN_GROUP_NODE;
}