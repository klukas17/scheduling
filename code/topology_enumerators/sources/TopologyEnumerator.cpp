//
// Created by mihael on 5/6/24.
//

#include "TopologyEnumerator.h"

TopologyEnumerator::TopologyEnumerator(Topology* topology) {
    this->topology = topology;
    for (auto [element_id, element] : topology->getTopologyElementsMap()) {
        auto element_type = element->getTopologyElementType();
        if (element_type == MACHINE_TOPOLOGY_ELEMENT || element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT || element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
            this->machines_with_algorithms.insert(element_id);
        }
    }
}

TopologyEnumerator::~TopologyEnumerator() = default;
