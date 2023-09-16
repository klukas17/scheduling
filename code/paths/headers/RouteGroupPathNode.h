//
// Created by mihael on 8/20/23.
//

/**
 * @file RouteGroupPathNode.h
 * @brief Defines the RouteGroupPathNode class for representing route group nodes in a path through a topology.
 */

#ifndef SCHEDULING_ROUTEGROUPPATHNODE_H
#define SCHEDULING_ROUTEGROUPPATHNODE_H

#include "GroupPathNode.h"

/**
 * @class RouteGroupPathNode
 * @brief Represents route group nodes in a path through a topology.
 *
 * The RouteGroupPathNode class is a derived class of GroupPathNode and represents route group nodes within a path through a topology.
 * Each route group node is associated with a topology element and has a single next path node connected to it.
 * This class provides an interface for working with route group nodes and their next path node.
 */
class RouteGroupPathNode : public GroupPathNode {
private:
    PathNode* next; /**< Pointer to the next path node connected to this route group node. */
public:
    /**
     * @brief Constructs a RouteGroupPathNode object associated with the provided topology element.
     * @param topology_element A pointer to the associated topology element.
     */
    explicit RouteGroupPathNode(long path_node_id, TopologyElement* topology_element);

    /**
     * @brief Retrieves the next path node connected to this route group node.
     * @return A pointer to the next path node.
     */
    PathNode* getNext();

    /**
     * @brief Sets the next path node connected to this route group node.
     * @param path_node A pointer to the next path node to connect.
     */
    void setNext(PathNode* path_node);
};

#endif //SCHEDULING_ROUTEGROUPPATHNODE_H
