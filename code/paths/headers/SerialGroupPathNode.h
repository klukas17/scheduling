//
// Created by mihael on 8/20/23.
//

/**
 * @file SerialGroupPathNode.h
 * @brief Defines the SerialGroupPathNode class for representing serial group nodes in a path through a topology.
 */

#ifndef SCHEDULING_SERIALGROUPPATHNODE_H
#define SCHEDULING_SERIALGROUPPATHNODE_H

#include "GroupPathNode.h"

/**
 * @class SerialGroupPathNode
 * @brief Represents serial group nodes in a path through a topology.
 *
 * The SerialGroupPathNode class is a derived class of GroupPathNode and represents serial group nodes within a path through a topology.
 * Each serial group node is associated with a topology element and can have a next path node connected to it.
 * This class provides an interface for working with serial group nodes.
 */
class SerialGroupPathNode : public GroupPathNode {
private:
    PathNode* next; /**< Pointer to the next path node in the sequence. */
public:
    /**
     * @brief Constructs a SerialGroupPathNode object associated with the provided topology element.
     * @param topology_element A pointer to the associated topology element.
     */
    explicit SerialGroupPathNode(long path_node_id, TopologyElement* topology_element);

    /**
     * @brief Retrieves the next path node connected to this serial group node.
     * @return A pointer to the next path node in the sequence, or nullptr if no node is connected.
     */
    PathNode* getNext();

    /**
     * @brief Sets the next path node connected to this serial group node.
     * @param path_node A pointer to the next path node to connect.
     */
    void setNext(PathNode* path_node);
};

#endif //SCHEDULING_SERIALGROUPPATHNODE_H
