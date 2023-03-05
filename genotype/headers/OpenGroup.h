//
// Created by mihael on 05/03/23.
//

#ifndef SCHEDULING_OPENGROUP_H
#define SCHEDULING_OPENGROUP_H

#include "TopologyElement.h"
#include "vector"

class OpenGroup : TopologyElement {
public:
    long group_id;

    std::vector<TopologyElement*> elements;
};


#endif //SCHEDULING_OPENGROUP_H
