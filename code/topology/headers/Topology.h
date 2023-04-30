//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_TOPOLOGY_H
#define SCHEDULING_TOPOLOGY_H

#include "TopologyElement.h"

class Topology {
private:
    TopologyElement* topology_root_element;
public:
    explicit Topology(TopologyElement* topology_root_element);
    TopologyElement* getRootElement();
};


#endif //SCHEDULING_TOPOLOGY_H
