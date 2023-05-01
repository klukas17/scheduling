//
// Created by mihael on 01/05/23.
//

#include "RouteGroup.h"

RouteGroup::RouteGroup(long id) : Group(id) {
    this->topology_element_type = ROUTE_GROUP_TOPOLOGY_ELEMENT;
}