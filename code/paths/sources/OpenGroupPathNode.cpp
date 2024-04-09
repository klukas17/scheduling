//
// Created by mihael on 8/20/23.
//

#include "OpenGroupPathNode.h"

OpenGroupPathNode::OpenGroupPathNode(long const path_node_id, TopologyElement* topology_element) : GroupPathNode(path_node_id, topology_element) {
    this->next = nullptr;
}

PathNode *OpenGroupPathNode::getNext() const {
    return next;
}

void OpenGroupPathNode::setNext(PathNode *path_node) {
    this->next = path_node;
}

std::vector<std::pair<long, PathNode*>> OpenGroupPathNode::getSubPathNodes() {
    return sub_path_nodes;
}

void OpenGroupPathNode::addSubPathNode(long id, PathNode *path_node) {
    this->sub_path_nodes.emplace_back(id, path_node);
}

std::map<long, PathNode*> OpenGroupPathNode::getChildren() const {
    return children;
}

void OpenGroupPathNode::addChild(PathNode* path_node, long const path_node_id) {
    children[path_node_id] = path_node;
}

