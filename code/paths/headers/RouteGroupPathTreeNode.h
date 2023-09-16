//
// Created by mihael on 9/3/23.
//

/**
 * @file RouteGroupPathTreeNode.h
 * @brief Defines the RouteGroupPathTreeNode class for representing route group nodes in a tree representation of paths through a topology.
 */

#ifndef SCHEDULING_ROUTEGROUPPATHTREENODE_H
#define SCHEDULING_ROUTEGROUPPATHTREENODE_H

#include "GroupPathTreeNode.h"

/**
 * @class RouteGroupPathTreeNode
 * @brief Represents a route group node in a tree representation of paths through a topology.
 *
 * The RouteGroupPathTreeNode class is a derived class of GroupPathTreeNode and is used to represent route group nodes
 * in a tree structure that represents paths through a topology. Route group nodes denote alternative path routes
 * that can be taken within a group of path steps.
 */
class RouteGroupPathTreeNode : public GroupPathTreeNode {
public:
    /**
     * @brief Constructs a RouteGroupPathTreeNode object with the specified PathNode.
     * @param path_node A pointer to the PathNode associated with this route group node.
     */
    explicit RouteGroupPathTreeNode(PathNode* path_node);
};

#endif //SCHEDULING_ROUTEGROUPPATHTREENODE_H
