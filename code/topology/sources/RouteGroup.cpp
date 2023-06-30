//
// Created by mihael on 01/05/23.
//

/**
 * @file RouteGroup.cpp
 * @brief Implements the member functions of the RouteGroup class.
 */

#include "RouteGroup.h"

RouteGroup::RouteGroup(long id) : Group(id) {
    this->topology_element_type = ROUTE_GROUP_TOPOLOGY_ELEMENT;
}
