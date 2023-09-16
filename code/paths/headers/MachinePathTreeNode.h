//
// Created by mihael on 9/3/23.
//

/**
 * @file MachinePathTreeNode.h
 * @brief Defines the MachinePathTreeNode class for representing machine nodes in a tree representation of paths through a topology.
 */

#ifndef SCHEDULING_MACHINEPATHTREENODE_H
#define SCHEDULING_MACHINEPATHTREENODE_H

#include "PathTreeNode.h"

/**
 * @class MachinePathTreeNode
 * @brief Represents a machine node in a tree representation of paths through a topology.
 *
 * The MachinePathTreeNode class is a derived class of PathTreeNode and is used to represent machine nodes
 * in a tree structure that represents paths through a topology. It is a specialized type of path tree node
 * that corresponds to a specific machine in the topology.
 */
class MachinePathTreeNode : public PathTreeNode {
public:
    /**
     * @brief Constructs a MachinePathTreeNode object with the specified PathNode.
     * @param path_node A pointer to the PathNode associated with this machine node.
     */
    explicit MachinePathTreeNode(PathNode* path_node);
};

#endif //SCHEDULING_MACHINEPATHTREENODE_H
