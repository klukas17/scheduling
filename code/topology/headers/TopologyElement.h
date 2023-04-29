//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_TOPOLOGYELEMENT_H
#define SCHEDULING_TOPOLOGYELEMENT_H

#include "TopologyElementType.h"

class TopologyElement {
protected:
    TopologyElementType topology_element_type;
public:
    TopologyElement();
    virtual ~TopologyElement() = 0;
};


#endif //SCHEDULING_TOPOLOGYELEMENT_H
