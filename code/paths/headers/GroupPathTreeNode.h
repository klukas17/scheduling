//
// Created by mihael on 9/3/23.
//

/**
 * @file GroupPathTreeNode.h
 * @brief Defines the GroupPathTreeNode class for representing group nodes in a tree representation of paths through a topology.
 */

#ifndef SCHEDULING_GROUPPATHTREENODE_H
#define SCHEDULING_GROUPPATHTREENODE_H

#include "PathTreeNode.h"
#include "vector"

/**
 * @class GroupPathTreeNode
 * @brief Represents a group node in a tree representation of paths through a topology.
 *
 * The GroupPathTreeNode class is a derived class of PathTreeNode and is used to represent group nodes
 * in a tree structure that represents paths through a topology. It contains a vector of child nodes.
 */
class GroupPathTreeNode : public PathTreeNode {
private:
    std::vector<PathTreeNode*> children; /**< A vector of child nodes associated with this group node. */

public:
    /**
     * @brief Constructs a GroupPathTreeNode object with the specified PathNode.
     * @param path_node A pointer to the PathNode associated with this group node.
     */
    explicit GroupPathTreeNode(PathNode* path_node);

    /**
     * @brief Virtual destructor for the GroupPathTreeNode class.
     *
     * This is a pure virtual destructor, making GroupPathTreeNode an abstract class.
     */
    ~GroupPathTreeNode() override = 0;

    /**
     * @brief Retrieves the vector of child nodes associated with this group node.
     * @return A vector containing pointers to child nodes.
     */
    std::vector<PathTreeNode*> getChildren();

    /**
     * @brief Adds a child node to this group node.
     * @param path_tree_node A pointer to the child node to add.
     */
    void addChild(PathTreeNode* path_tree_node);
};

#endif //SCHEDULING_GROUPPATHTREENODE_H
