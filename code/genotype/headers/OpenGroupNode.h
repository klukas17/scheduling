//
// Created by mihael on 01/05/23.
//

/**
 * @file OpenGroupNode.h
 * @brief Defines the OpenGroupNode class for representing an open group node within an individual's genotype.
 */

#ifndef SCHEDULING_OPENGROUPNODE_H
#define SCHEDULING_OPENGROUPNODE_H

#include "GroupNode.h"

/**
 * @class OpenGroupNode
 * @brief Represents an open group node within an individual's genotype.
 *
 * The OpenGroupNode class is derived from the GroupNode class and represents a node in an individual's genotype that
 * signifies an open group of nodes. It inherits attributes for a group of nodes and represents nodes that can be added
 * dynamically and don't have a predetermined structure.
 */
class OpenGroupNode : public GroupNode {
public:
    /**
     * @brief Constructs an OpenGroupNode object with the provided identifier.
     * @param id The identifier for the open group node.
     */
    explicit OpenGroupNode(long id);
};

#endif //SCHEDULING_OPENGROUPNODE_H
