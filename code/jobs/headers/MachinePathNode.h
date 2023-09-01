//
// Created by mihael on 8/20/23.
//

/**
 * @file MachinePathNode.h
 * @brief Defines the MachinePathNode class for representing machine nodes in a path through a topology.
 */

#ifndef SCHEDULING_MACHINEPATHNODE_H
#define SCHEDULING_MACHINEPATHNODE_H

#include "PathNode.h"

/**
 * @class MachinePathNode
 * @brief Represents machine nodes in a path through a topology.
 *
 * The MachinePathNode class is a derived class of PathNode and represents machine nodes within a path through a topology.
 * Each machine node is associated with a topology element and can have a next path node connected to it.
 * This class provides an interface for working with machine nodes.
 */
class MachinePathNode : public PathNode {
private:
    PathNode* next; /**< Pointer to the next path node in the sequence. */
public:
    /**
     * @brief Constructs a MachinePathNode object associated with the provided topology element.
     * @param topology_element A pointer to the associated topology element.
     */
    explicit MachinePathNode(TopologyElement* topology_element);

    /**
     * @brief Retrieves the next path node connected to this machine node.
     * @return A pointer to the next path node in the sequence, or nullptr if no node is connected.
     */
    PathNode* getNext();

    /**
     * @brief Sets the next path node connected to this machine node.
     * @param path_node A pointer to the next path node to connect.
     */
    void setNext(PathNode* path_node);
};

#endif //SCHEDULING_MACHINEPATHNODE_H
