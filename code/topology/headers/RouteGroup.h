//
// Created by mihael on 01/05/23.
//

/**
 * @file RouteGroup.h
 * @brief Defines the RouteGroup class for representing a route group in a topology.
 */

#ifndef SCHEDULING_ROUTEGROUP_H
#define SCHEDULING_ROUTEGROUP_H

#include "Group.h"

/**
 * @class RouteGroup
 * @brief Represents a route group in a topology.
 *
 * The RouteGroup class is a derived class of the Group class and represents a route group in a topology.
 * It inherits attributes and functionality from the Group class.
 */
class RouteGroup : public Group {
public:
    /**
     * @brief Constructs a RouteGroup object with the given ID.
     * @param id The ID of the route group.
     */
    explicit RouteGroup(long id);
};

#endif //SCHEDULING_ROUTEGROUP_H
