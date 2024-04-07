//
// Created by mihael on 29/04/23.
//

#include "Topology.h"
#include "SchedulingError.h"
#include "MachinePathNode.h"
#include "SerialGroup.h"
#include "ParallelGroup.h"
#include "RouteGroup.h"
#include "OpenGroup.h"

Topology::Topology(TopologyElement* topology_root_element) {
    this->topology_root_element = topology_root_element;
    indexTopologyElements(topology_root_element);
    buildPriorityMap();
}

TopologyElement* Topology::getRootElement() const {
    return topology_root_element;
}

std::map<long, TopologyElement *> Topology::getTopologyElementsMap() {
    return topology_elements_map;
}

void Topology::indexTopologyElements(TopologyElement* node) {

    switch (node->getTopologyElementType()) {

        case ABSTRACT_TOPOLOGY_ELEMENT:
            throw SchedulingError("Abstract topology element encountered in Topology::indexPathNodes function.");

        case MACHINE_TOPOLOGY_ELEMENT:
            topology_elements_map[node->getId()] = node;
            break;

        case SERIAL_GROUP_TOPOLOGY_ELEMENT:
            topology_elements_map[node->getId()] = node;
            for (auto const child : dynamic_cast<SerialGroup*>(node)->getChildren()) {
                indexTopologyElements(child);
            }
            break;

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
            topology_elements_map[node->getId()] = node;
            for (auto const child : dynamic_cast<ParallelGroup*>(node)->getChildren()) {
                indexTopologyElements(child);
            }
            break;

        case ROUTE_GROUP_TOPOLOGY_ELEMENT:
            topology_elements_map[node->getId()] = node;
            for (auto const child : dynamic_cast<RouteGroup*>(node)->getChildren()) {
                indexTopologyElements(child);
            }
            break;

        case OPEN_GROUP_TOPOLOGY_ELEMENT:
            topology_elements_map[node->getId()] = node;
            for (auto const child : dynamic_cast<OpenGroup*>(node)->getChildren()) {
                indexTopologyElements(child);
            }
            break;
    }
}

void Topology::buildPriorityMap() {
    for (auto [machine_id, machine] : topology_elements_map) {
        for (auto predecessor_id : machine->getPredecessorIds()) {
            priority_map[machine_id][predecessor_id] = 1;
            priority_map[predecessor_id][machine_id] = -1;
        }
    }
}

long Topology::getPriorityValue(long const machine_id_1, long const machine_id_2) {
    return priority_map[machine_id_1][machine_id_2];
}