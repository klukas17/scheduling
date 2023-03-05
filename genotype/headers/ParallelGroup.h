//
// Created by mihael on 05/03/23.
//

#ifndef SCHEDULING_PARALLELGROUP_H
#define SCHEDULING_PARALLELGROUP_H

#include "TopologyElement.h"
#include "vector"

class ParallelGroup : TopologyElement {
public:
    long group_id;

    std::vector<TopologyElement*> elements;
};


#endif //SCHEDULING_PARALLELGROUP_H
