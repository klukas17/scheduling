//
// Created by mihael on 9/3/23.
//

/**
 * @file GroupPathTreeNode.cpp
 * @brief Implements the member functions of the GroupPathTreeNode class.
 */

#include "GroupPathTreeNode.h"

GroupPathTreeNode::GroupPathTreeNode(PathNode *path_node) : PathTreeNode(path_node) {}

GroupPathTreeNode::~GroupPathTreeNode() = default;

std::vector<PathTreeNode *> GroupPathTreeNode::getChildren() {
    return children;
}

void GroupPathTreeNode::addChild(PathTreeNode *path_tree_node) {
    children.push_back(path_tree_node);
}