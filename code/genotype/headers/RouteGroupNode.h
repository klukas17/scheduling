//
// Created by mihael on 01/05/23.
//

/**
 * @file RouteGroupNode.h
 * @brief Defines the RouteGroupNode class for representing a route group node within an individual's genotype.
 */

#ifndef SCHEDULING_ROUTEGROUPNODE_H
#define SCHEDULING_ROUTEGROUPNODE_H

#include "GroupNode.h"

/**
 * @class RouteGroupNode
 * @brief Represents a route group node within an individual's genotype.
 *
 * The RouteGroupNode class is derived from the GroupNode class and represents a node in an individual's genotype that
 * signifies a route group of nodes. It inherits attributes for a group of nodes and represents nodes that define a
 * specific routing path.
 */
class RouteGroupNode : public GroupNode {
public:
    /**
     * @brief Constructs a RouteGroupNode object with the provided identifier.
     * @param id The identifier for the route group node.
     */
    explicit RouteGroupNode(long id);
};

#endif //SCHEDULING_ROUTEGROUPNODE_H
