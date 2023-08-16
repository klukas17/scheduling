//
// Created by mihael on 8/15/23.
//

/**
 * @file OpenGroupPathNode.h
 * @brief Defines the OpenGroupPathNode class for representing a open group node within a topology path.
 */

#ifndef SCHEDULING_OPENGROUPPATHNODE_H
#define SCHEDULING_OPENGROUPPATHNODE_H

#include "GroupPathNode.h"
#include <vector>

/**
 * @class OpenGroupPathNode
 * @brief Represents a node within a open group node within a topology path.
 *
 * The OpenGroupPathNode class is a derived class of GroupPathNode, representing a node within a topology path that is specific to an open group.
 * It contains information about the associated topology element, its group-specific element types, a pointer to the next node in the path, and a vector of pointers to sub-path nodes.
 */
class OpenGroupPathNode : public GroupPathNode {
private:
    PathNode* next; /**< A pointer to the next node in the open group-specific topology path. */
    std::vector<PathNode*> sub_path_nodes; /**< A vector of pointers to sub-path nodes within the open group-specific path. */
public:
    /**
     * @brief Constructs an OpenGroupPathNode object with the given topology element.
     * @param topology_element The associated topology element of the open group-specific path node.
     */
    explicit OpenGroupPathNode(TopologyElement* topology_element);

    /**
     * @brief Retrieves the pointer to the next node in the open group-specific topology path.
     * @return A pointer to the next node in the open group-specific topology path.
     */
    PathNode* getNext();

    /**
     * @brief Sets the pointer to the next node in the open group-specific topology path.
     * @param next A pointer to the next node to set.
     */
    void setNext(PathNode* next);

    /**
     * @brief Retrieves the vector of pointers to sub-path nodes within the open group-specific topology path.
     * @return A vector containing pointers to sub-path nodes.
     */
    std::vector<PathNode*> getSubPathNodes();

    /**
     * @brief Adds a pointer to a sub-path node within the open group-specific topology path.
     * @param sub_path_node A pointer to the sub-path node to add.
     */
    void addSubPathNode(PathNode* sub_path_node);
};

#endif // SCHEDULING_OPENGROUPPATHNODE_H
