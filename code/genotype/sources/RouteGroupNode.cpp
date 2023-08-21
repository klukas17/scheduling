//
// Created by mihael on 01/05/23.
//

/**
 * @file RouteGroupNode.cpp
 * @brief Implements the member functions of the RouteGroupNode class.
 */

#include "RouteGroupNode.h"

RouteGroupNode::RouteGroupNode(long id) : GroupNode(id) {
    this->node_type = ROUTE_GROUP_NODE;
}