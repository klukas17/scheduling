//
// Created by mihael on 8/20/23.
//

#include "RouteGroupPathNode.h"

RouteGroupPathNode::RouteGroupPathNode(long const path_node_id, TopologyElement* topology_element) : GroupPathNode(path_node_id, topology_element) {
    this->next = nullptr;
}

PathNode *RouteGroupPathNode::getNext() const {
    return next;
}

void RouteGroupPathNode::setNext(PathNode *path_node) {
    this->next = path_node;
}