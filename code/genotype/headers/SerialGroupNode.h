//
// Created by mihael on 30/04/23.
//

/**
 * @file SerialGroupNode.h
 * @brief Defines the SerialGroupNode class for representing a serial group node within an individual's genotype.
 */

#ifndef SCHEDULING_SERIALGROUPNODE_H
#define SCHEDULING_SERIALGROUPNODE_H

#include "GroupNode.h"

/**
 * @class SerialGroupNode
 * @brief Represents a serial group node within an individual's genotype.
 *
 * The SerialGroupNode class is derived from the GroupNode class and represents a node in an individual's genotype that
 * signifies a serial group of nodes. It inherits attributes for a group of nodes and represents nodes that are executed
 * in sequence.
 */
class SerialGroupNode : public GroupNode {
public:
    /**
     * @brief Constructs a SerialGroupNode object with the provided identifier.
     * @param id The identifier for the serial group node.
     */
    explicit SerialGroupNode(long id);
};

#endif //SCHEDULING_SERIALGROUPNODE_H
