//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_TOPOLOGYELEMENT_H
#define SCHEDULING_TOPOLOGYELEMENT_H

#include "TopologyElementType.h"
#include "set"

class TopologyElement {
protected:
    long id;
    TopologyElementType topology_element_type;
    GeneralTopologyElementType general_topology_element_type;
    std::set<long> predecessor_element_ids;
public:
    explicit TopologyElement(long id);
    virtual ~TopologyElement() = 0;
    [[nodiscard]] long getId() const;
    TopologyElementType getTopologyElementType();
    GeneralTopologyElementType getGeneralTopologyElementType();
    std::set<long> getPredecessorIds();
    void addPredecessorId(long element_id);
};


#endif //SCHEDULING_TOPOLOGYELEMENT_H
