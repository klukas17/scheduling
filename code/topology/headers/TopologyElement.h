//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_TOPOLOGYELEMENT_H
#define SCHEDULING_TOPOLOGYELEMENT_H

#include "TopologyElementType.h"
#include "Breakdown.h"
#include <set>
#include "vector"

class TopologyElement {
protected:
    long id;
    TopologyElementType topology_element_type;
    GeneralTopologyElementType general_topology_element_type;
    std::set<long> predecessor_element_ids;
    std::vector<Breakdown*> breakdowns;
    long buffer_size;
public:
    explicit TopologyElement(long id);
    virtual ~TopologyElement() = 0;
    [[nodiscard]] long getId() const;
    [[nodiscard]] TopologyElementType getTopologyElementType() const;
    [[nodiscard]] GeneralTopologyElementType getGeneralTopologyElementType() const;
    std::set<long> getPredecessorIds();
    void addPredecessorId(long element_id);
    std::vector<Breakdown*> getBreakdowns();
    void addBreakdown(Breakdown* breakdown);
    [[nodiscard]] long getBufferSize() const;
    void setBufferSize(long buffer_size);
};

#endif //SCHEDULING_TOPOLOGYELEMENT_H
