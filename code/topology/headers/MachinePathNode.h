//
// Created by mihael on 8/15/23.
//

/**
 * @file MachinePathNode.h
 * @brief Defines the MachinePathNode class for representing a machine-specific node within a topology path.
 */

#ifndef SCHEDULING_MACHINEPATHNODE_H
#define SCHEDULING_MACHINEPATHNODE_H

#include "PathNode.h"

/**
 * @class MachinePathNode
 * @brief Represents a machine node within a topology path.
 *
 * The MachinePathNode class is a derived class of PathNode, representing a node within a topology path that is specific to a machine.
 * It contains information about the associated topology element, its element types, and a pointer to the next node in the path.
 */
class MachinePathNode : public PathNode {
private:
    PathNode* next; /**< A pointer to the next node in the topology path. */
public:
    /**
     * @brief Constructs a MachinePathNode object with the given topology element.
     * @param topology_element The associated topology element of the machine path node.
     */
    explicit MachinePathNode(TopologyElement* topology_element);

    /**
     * @brief Retrieves the pointer to the next node in the topology path.
     * @return A pointer to the next node in the topology path.
     */
    PathNode* getNext();

    /**
     * @brief Sets the pointer to the next node in the topology path.
     * @param next A pointer to the next node to set.
     */
    void setNext(PathNode* next);
};

#endif // SCHEDULING_MACHINEPATHNODE_H
