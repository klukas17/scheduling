//
// Created by mihael on 8/15/23.
//

/**
 * @file PathNode.h
 * @brief Defines the PathNode class for representing a node within a topology path.
 */

#ifndef SCHEDULING_PATHNODE_H
#define SCHEDULING_PATHNODE_H

#include "TopologyElement.h"

/**
 * @class PathNode
 * @brief Represents a node within a topology path.
 *
 * The PathNode class represents a node within a topology path and contains information about the associated topology element
 * and its element types.
 */
class PathNode {
protected:
    TopologyElement* topology_element; /**< The associated topology element of the path node. */
public:
    /**
     * @brief Constructs a PathNode object with the given topology element.
     * @param topology_element The associated topology element of the path node.
     */
    explicit PathNode(TopologyElement* topology_element);

    /**
     * @brief Destructor for the PathNode class.
     *
     * This is a pure virtual destructor, making PathNode an abstract class.
     */
    virtual ~PathNode() = 0;

    /**
     * @brief Retrieves the associated topology element of the path node.
     * @return A pointer to the associated topology element.
     */
    TopologyElement* getTopologyElement();
};

#endif // SCHEDULING_PATHNODE_H

