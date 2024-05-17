//
// Created by mihael on 5/5/24.
//

#include "OnlineSchedulingAlgorithmClusterGenotypeBlueprint.h"

OnlineSchedulingAlgorithmClusterGenotypeBlueprint::OnlineSchedulingAlgorithmClusterGenotypeBlueprint(Topology* topology) {
    this->topology = topology;
    for (auto [element_id, element] : topology->getTopologyElementsMap()) {
        auto element_type = element->getTopologyElementType();
        if (element_type == MACHINE_TOPOLOGY_ELEMENT || element_type == PARALLEL_GROUP_TOPOLOGY_ELEMENT || element_type == OPEN_GROUP_TOPOLOGY_ELEMENT) {
            topology_elements_with_algorithms.insert(element_id);
        } else {
            topology_elements_without_algorithms.insert(element_id);
        }
    }
}
