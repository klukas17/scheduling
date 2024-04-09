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

std::map<long, PathNode*> RouteGroupPathNode::getChildren() const {
    return children;
}

void RouteGroupPathNode::addChild(PathNode* path_node, long const path_node_id) {
    children[path_node_id] = path_node;
}
