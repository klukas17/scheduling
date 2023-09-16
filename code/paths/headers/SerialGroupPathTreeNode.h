//
// Created by mihael on 9/3/23.
//

/**
 * @file SerialGroupPathTreeNode.h
 * @brief Defines the SerialGroupPathTreeNode class for representing serial group nodes in a tree representation of paths through a topology.
 */

#ifndef SCHEDULING_SERIALGROUPPATHTREENODE_H
#define SCHEDULING_SERIALGROUPPATHTREENODE_H

#include "GroupPathTreeNode.h"

/**
 * @class SerialGroupPathTreeNode
 * @brief Represents a serial group node in a tree representation of paths through a topology.
 *
 * The SerialGroupPathTreeNode class is a derived class of GroupPathTreeNode and is used to represent serial group nodes
 * in a tree structure that represents paths through a topology. Serial group nodes denote a sequence of path steps
 * that must be executed in order.
 */
class SerialGroupPathTreeNode : public GroupPathTreeNode {
public:
    /**
     * @brief Constructs a SerialGroupPathTreeNode object with the specified PathNode.
     * @param path_node A pointer to the PathNode associated with this serial group node.
     */
    explicit SerialGroupPathTreeNode(PathNode* path_node);
};

#endif //SCHEDULING_SERIALGROUPPATHTREENODE_H
