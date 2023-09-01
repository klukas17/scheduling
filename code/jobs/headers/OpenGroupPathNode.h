//
// Created by mihael on 8/20/23.
//

/**
 * @file OpenGroupPathNode.h
 * @brief Defines the OpenGroupPathNode class for representing open group nodes in a path through a topology.
 */

#ifndef SCHEDULING_OPENGROUPPATHNODE_H
#define SCHEDULING_OPENGROUPPATHNODE_H

#include "GroupPathNode.h"
#include "tuple"

/**
 * @class OpenGroupPathNode
 * @brief Represents open group nodes in a path through a topology.
 *
 * The OpenGroupPathNode class is a derived class of GroupPathNode and represents open group nodes within a path through a topology.
 * Each open group node is associated with a topology element and has a single next path node connected to it, along with a list of sub-path nodes.
 * Sub-path nodes are connected to this open group node and are associated with unique identifiers.
 * This class provides an interface for working with open group nodes, their next path node, and sub-path nodes.
 */
class OpenGroupPathNode : public GroupPathNode {
private:
    PathNode* next; /**< Pointer to the next path node connected to this open group node. */
    std::vector<std::pair<long, PathNode*>> sub_path_nodes; /**< List of sub-path nodes associated with unique identifiers. */
public:
    /**
     * @brief Constructs an OpenGroupPathNode object associated with the provided topology element.
     * @param topology_element A pointer to the associated topology element.
     */
    explicit OpenGroupPathNode(TopologyElement* topology_element);

    /**
     * @brief Retrieves the next path node connected to this open group node.
     * @return A pointer to the next path node.
     */
    PathNode* getNext();

    /**
     * @brief Sets the next path node connected to this open group node.
     * @param path_node A pointer to the next path node to connect.
     */
    void setNext(PathNode* path_node);

    /**
     * @brief Retrieves the list of sub-path nodes associated with this open group node.
     * @return A vector of pairs containing unique identifiers and corresponding sub-path nodes.
     */
    std::vector<std::pair<long, PathNode*>> getSubPathNodes();

    /**
     * @brief Adds a sub-path node to this open group node.
     * @param id The unique identifier for the sub-path node.
     * @param path_node A pointer to the sub-path node to add.
     */
    void addSubPathNode(long id, PathNode* path_node);
};

#endif //SCHEDULING_OPENGROUPPATHNODE_H
