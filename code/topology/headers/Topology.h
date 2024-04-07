//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_TOPOLOGY_H
#define SCHEDULING_TOPOLOGY_H

#include "TopologyElement.h"
#include <map>

class Topology {
    TopologyElement* topology_root_element;
    std::map<long, TopologyElement*> topology_elements_map;
    std::map<long, std::map<long, long>> priority_map;
public:
    explicit Topology(TopologyElement* topology_root_element);
    [[nodiscard]] TopologyElement* getRootElement() const;
    std::map<long, TopologyElement*> getTopologyElementsMap();
    void indexTopologyElements(TopologyElement* node);
    void buildPriorityMap();
    long getPriorityValue(long machine_id_1, long machine_id_2);
};

#endif //SCHEDULING_TOPOLOGY_H
