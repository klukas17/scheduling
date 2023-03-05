//
// Created by mihael on 06/03/23.
//

#ifndef SCHEDULING_ROUTEGROUP_H
#define SCHEDULING_ROUTEGROUP_H

#include "TopologyElement.h"
#include "vector"

class RouteGroup : TopologyElement {
public:
    long group_id;
    std::vector<TopologyElement*> elements;
};


#endif //SCHEDULING_ROUTEGROUP_H
