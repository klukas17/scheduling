//
// Created by mihael on 9/3/23.
//

/**
 * @file PathTreeNode.h
 * @brief Defines the PathTreeNode class for representing nodes in a tree representation of paths through a topology.
 */

#ifndef SCHEDULING_PATHTREENODE_H
#define SCHEDULING_PATHTREENODE_H

#include "PathNode.h"

/**
 * @class PathTreeNode
 * @brief Represents a node in a tree representation of paths through a topology.
 *
 * The PathTreeNode class is a base class for representing nodes in a tree structure that represents paths
 * through a topology. It encapsulates a pointer to a PathNode object, which represents a step in a path.
 */
class PathTreeNode {
private:
    PathNode* path_node; /**< A pointer to the PathNode associated with this tree node. */

public:
    /**
     * @brief Constructs a PathTreeNode object with the specified PathNode.
     * @param path_node A pointer to the PathNode associated with this tree node.
     */
    explicit PathTreeNode(PathNode* path_node);

    /**
     * @brief Virtual destructor for the PathTreeNode class.
     *
     * This is a pure virtual destructor, making PathTreeNode an abstract class.
     */
    virtual ~PathTreeNode() = 0;

    /**
     * @brief Retrieves the PathNode associated with this tree node.
     * @return A pointer to the associated PathNode.
     */
    PathNode* getPathNode();

    /**
     * @brief Deletes the PathTreeNode object.
     *
     * This function is used to delete the PathTreeNode object, and it should be implemented in derived classes.
     */
    void deletePathTreeNode();
};

#endif //SCHEDULING_PATHTREENODE_H
