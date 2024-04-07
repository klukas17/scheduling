//
// Created by mihael on 01/05/23.
//

#include "RouteGroupNode.h"

RouteGroupNode::RouteGroupNode(long const id) : GroupNode(id) {
    this->node_type = ROUTE_GROUP_NODE;
}