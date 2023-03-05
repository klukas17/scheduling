//
// Created by mihael on 05/03/23.
//

#ifndef SCHEDULING_SERIALGROUP_H
#define SCHEDULING_SERIALGROUP_H

#include "TopologyElement.h"
#include "vector"

class SerialGroup : TopologyElement {
public:
    long group_id;
    std::vector<TopologyElement*> elements;
};


#endif //SCHEDULING_SERIALGROUP_H
