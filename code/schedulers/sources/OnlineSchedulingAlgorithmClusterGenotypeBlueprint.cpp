//
// Created by mihael on 5/5/24.
//

#include "OnlineSchedulingAlgorithmClusterGenotypeBlueprint.h"

OnlineSchedulingAlgorithmClusterGenotypeBlueprint::OnlineSchedulingAlgorithmClusterGenotypeBlueprint(Topology* topology) {
    this->topology = topology;
    for (auto [element_id, element] : topology->getTopologyElementsMap()) {
        auto element_type = element->getTopologyElementType();
        switch (element_type) {
        case MACHINE_TOPOLOGY_ELEMENT:
            topology_elements_with_algorithms_in_leaves.insert(element_id);
            break;
        case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
        case ROUTE_GROUP_TOPOLOGY_ELEMENT:
            topology_elements_with_algorithms_in_inner_nodes.insert(element_id);
            break;
        default:
            topology_elements_without_algorithms.insert(element_id);
            break;
        }
    }
}
