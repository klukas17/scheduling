//
// Created by mihael on 8/20/23.
//

/**
 * @file ParallelGroupPathNode.h
 * @brief Defines the ParallelGroupPathNode class for representing parallel group nodes in a path through a topology.
 */

#ifndef SCHEDULING_PARALLELGROUPPATHNODE_H
#define SCHEDULING_PARALLELGROUPPATHNODE_H

#include "GroupPathNode.h"

/**
 * @class ParallelGroupPathNode
 * @brief Represents parallel group nodes in a path through a topology.
 *
 * The ParallelGroupPathNode class is a derived class of GroupPathNode and represents parallel group nodes within a path through a topology.
 * Each parallel group node is associated with a topology element and can have multiple next path nodes connected to it, each associated with a unique identifier.
 * This class provides an interface for working with parallel group nodes and their multiple next path nodes.
 */
class ParallelGroupPathNode : public GroupPathNode {
private:
    std::map<long, PathNode*> next; /**< Map of unique identifiers to pointers of next path nodes. */
public:
    /**
     * @brief Constructs a ParallelGroupPathNode object associated with the provided topology element.
     * @param topology_element A pointer to the associated topology element.
     */
    explicit ParallelGroupPathNode(long path_node_id, TopologyElement* topology_element);

    /**
     * @brief Retrieves a map of unique identifiers to the next path nodes connected to this parallel group node.
     * @return A map containing unique identifiers as keys and pointers to next path nodes as values.
     */
    std::map<long, PathNode*> getNext();

    /**
     * @brief Sets the next path node connected to this parallel group node with the specified unique identifier.
     * @param id The unique identifier associated with the next path node.
     * @param path_node A pointer to the next path node to connect.
     */
    void setNext(long id, PathNode* path_node);
};

#endif //SCHEDULING_PARALLELGROUPPATHNODE_H
