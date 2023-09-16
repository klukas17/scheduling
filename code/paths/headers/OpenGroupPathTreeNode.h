//
// Created by mihael on 9/3/23.
//

/**
 * @file OpenGroupPathTreeNode.h
 * @brief Defines the OpenGroupPathTreeNode class for representing open group nodes in a tree representation of paths through a topology.
 */

#ifndef SCHEDULING_OPENGROUPPATHTREENODE_H
#define SCHEDULING_OPENGROUPPATHTREENODE_H

#include "GroupPathTreeNode.h"

/**
 * @class OpenGroupPathTreeNode
 * @brief Represents an open group node in a tree representation of paths through a topology.
 *
 * The OpenGroupPathTreeNode class is a derived class of GroupPathTreeNode and is used to represent open group nodes
 * in a tree structure that represents paths through a topology. Open group nodes denote a group of path steps where
 * the order of execution is not defined and can vary.
 */
class OpenGroupPathTreeNode : public GroupPathTreeNode {
public:
    /**
     * @brief Constructs an OpenGroupPathTreeNode object with the specified PathNode.
     * @param path_node A pointer to the PathNode associated with this open group node.
     */
    explicit OpenGroupPathTreeNode(PathNode* path_node);
};

#endif //SCHEDULING_OPENGROUPPATHTREENODE_H
