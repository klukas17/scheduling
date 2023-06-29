//
// Created by mihael on 29/06/23.
//

#include "PathNode.h"

PathNode::PathNode(long machine_id) {
    this->machine_id = machine_id;
}

long PathNode::getMachineId() {
    return machine_id;
}

std::vector<Prerequisite *> PathNode::getPrerequisites() {
    return prerequisites;
}

void PathNode::addPrerequisite(Prerequisite *prerequisite) {
    prerequisites.push_back(prerequisite);
}

std::vector<PathNode *> PathNode::getChildren() {
    return children;
}

void PathNode::addChild(PathNode *child) {
    children.push_back(child);
}