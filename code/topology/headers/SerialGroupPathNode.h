//
// Created by mihael on 8/15/23.
//

/**
 * @file SerialGroupPathNode.h
 * @brief Defines the SerialGroupPathNode class for representing a serial group node within a topology path.
 */

/**
 * @file SerialGroupPathNode.h
 * @brief Defines the SerialGroupPathNode class for representing a serial group node within a topology path.
 */

#ifndef SCHEDULING_SERIALGROUPPATHNODE_H
#define SCHEDULING_SERIALGROUPPATHNODE_H

#include "GroupPathNode.h"
#include "vector"

/**
 * @class SerialGroupPathNode
 * @brief Represents a serial group node within a topology path.
 *
 * The SerialGroupPathNode class is a derived class of GroupPathNode, representing a node within a topology path that
 * is specific to a serial group. It contains information about the associated topology element, its group-specific
 * element types, a pointer to the next node in the path, and a list of child nodes.
 */
class SerialGroupPathNode : public GroupPathNode {
private:
    PathNode* next; /**< A pointer to the next node in the topology path. */
    std::vector<PathNode*> children; /**< A list of child nodes within the serial group. */
public:
    /**
     * @brief Constructs a SerialGroupPathNode object with the given topology element.
     * @param topology_element The associated topology element of the serial group-specific path node.
     */
    explicit SerialGroupPathNode(TopologyElement* topology_element);

    /**
     * @brief Retrieves the pointer to the next node in the topology path.
     * @return A pointer to the next node in the serial group-specific topology path.
     */
    PathNode* getNext();

    /**
     * @brief Sets the pointer to the next node in the topology path.
     * @param next A pointer to the next node to set.
     */
    void setNext(PathNode* next);

    /**
     * @brief Retrieves the list of child nodes within the serial group.
     * @return A vector containing pointers to the child nodes.
     */
    std::vector<PathNode*> getChildren();

    /**
     * @brief Adds a child node to the list of child nodes within the serial group.
     * @param path_node A pointer to the child node to be added.
     */
    void addChild(PathNode* path_node);
};

#endif // SCHEDULING_SERIALGROUPPATHNODE_H

