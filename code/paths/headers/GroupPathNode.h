//
// Created by mihael on 8/20/23.
//

/**
 * @file GroupPathNode.h
 * @brief Defines the GroupPathNode class for representing group nodes in a path through a topology.
 */

#ifndef SCHEDULING_GROUPPATHNODE_H
#define SCHEDULING_GROUPPATHNODE_H

#include "PathNode.h"

/**
 * @class GroupPathNode
 * @brief Represents group nodes in a path through a topology.
 *
 * The GroupPathNode class is a derived class of PathNode and represents group nodes within a path through a topology.
 * Each group node is associated with a topology element. This class provides an interface for working with group nodes.
 */
class GroupPathNode : public PathNode {
public:
    /**
     * @brief Constructs a GroupPathNode object associated with the provided topology element.
     * @param topology_element A pointer to the associated topology element.
     */
    explicit GroupPathNode(long path_node_id, TopologyElement* topology_element);

    /**
     * @brief Virtual destructor for GroupPathNode.
     *
     * This is a virtual destructor for the GroupPathNode class to allow for proper destruction of derived classes.
     */
    ~GroupPathNode() override = 0;
};

#endif //SCHEDULING_GROUPPATHNODE_H
