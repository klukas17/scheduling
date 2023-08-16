//
// Created by mihael on 29/06/23.
//

#include "PathNode.h"

PathNode::PathNode(TopologyElement* topology_element) {
    this->topology_element = topology_element;
}

TopologyElement *PathNode::getTopologyElement() {
    return topology_element;
}

std::vector<Prerequisite *> PathNode::getPrerequisites() {
    return prerequisites;
}

void PathNode::addPrerequisite(Prerequisite *prerequisite) {
    prerequisites.push_back(prerequisite);
}

std::map<long, PathNode*> PathNode::getChildren() {
    return children;
}

void PathNode::addChild(PathNode *child) {
    children[child->getTopologyElement()->getId()] = child;
}