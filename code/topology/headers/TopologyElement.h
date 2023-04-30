//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_TOPOLOGYELEMENT_H
#define SCHEDULING_TOPOLOGYELEMENT_H

#include "TopologyElementType.h"

class TopologyElement {
protected:
    long id;
    TopologyElementType topology_element_type;
public:
    explicit TopologyElement(long id);
    virtual ~TopologyElement() = 0;
    [[nodiscard]] long getId() const;
    TopologyElementType getTopologyElementType();
};


#endif //SCHEDULING_TOPOLOGYELEMENT_H
