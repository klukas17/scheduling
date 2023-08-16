//
// Created by mihael on 8/15/23.
//

/**
 * @file GroupPathNode.h
 * @brief Defines the GroupPathNode class for representing a group node within a topology path.
 */

#ifndef SCHEDULING_GROUPPATHNODE_H
#define SCHEDULING_GROUPPATHNODE_H

#include "PathNode.h"

/**
 * @class GroupPathNode
 * @brief Represents a group node within a topology path.
 *
 * The GroupPathNode class is a derived class of PathNode, representing a node within a topology path that is specific to a group.
 * It inherits the functionality of the base PathNode class and serves as a base class for specific group path nodes.
 */
class GroupPathNode : public PathNode {
public:
    /**
     * @brief Constructs a GroupPathNode object with the given topology element.
     * @param topology_element The associated topology element of the group-specific path node.
     */
    explicit GroupPathNode(TopologyElement* topology_element);

    /**
     * @brief Pure virtual destructor for the GroupPathNode class.
     *
     * This makes GroupPathNode an abstract class, and it cannot be instantiated directly.
     */
    ~GroupPathNode() override = 0;
};

#endif // SCHEDULING_GROUPPATHNODE_H
