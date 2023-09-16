//
// Created by mihael on 9/3/23.
//

/**
 * @file ParallelGroupPathTreeNode.h
 * @brief Defines the ParallelGroupPathTreeNode class for representing parallel group nodes in a tree representation of paths through a topology.
 */

#ifndef SCHEDULING_PARALLELGROUPPATHTREENODE_H
#define SCHEDULING_PARALLELGROUPPATHTREENODE_H

#include "GroupPathTreeNode.h"

/**
 * @class ParallelGroupPathTreeNode
 * @brief Represents a parallel group node in a tree representation of paths through a topology.
 *
 * The ParallelGroupPathTreeNode class is a derived class of GroupPathTreeNode and is used to represent parallel group nodes
 * in a tree structure that represents paths through a topology. Parallel group nodes denote a set of path steps that can
 * be executed concurrently, without a specific order.
 */
class ParallelGroupPathTreeNode : public GroupPathTreeNode {
public:
    /**
     * @brief Constructs a ParallelGroupPathTreeNode object with the specified PathNode.
     * @param path_node A pointer to the PathNode associated with this parallel group node.
     */
    explicit ParallelGroupPathTreeNode(PathNode* path_node);
};

#endif //SCHEDULING_PARALLELGROUPPATHTREENODE_H
