//
// Created by mihael on 29/04/23.
//

#include "Topology.h"

#include <queue>
#include <ranges>

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
    calculateMachineTraversalOrder();
}

TopologyElement* Topology::getRootElement() const {
    return topology_root_element;
}

std::map<long, TopologyElement *> Topology::getTopologyElementsMap() {
    return topology_elements_map;
}

std::vector<long> Topology::getMachineTraversalOrder() {
    return machine_traversal_order;
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

void Topology::calculateMachineTraversalOrder() {
    std::map<long, std::set<long>> predecessors, successors;
    for (auto machine_id : topology_elements_map | std::views::keys) {
        predecessors[machine_id] = {};
        successors[machine_id] = {};
    }
    buildPredecessorAndSuccessorMaps(predecessors, successors, getRootElement(), nullptr);
    std::queue<long> free_machines;
    for (const auto& [predecessor_id, predecessor_values] : predecessors) {
        if (predecessor_values.empty()) {
            free_machines.push(predecessor_id);
        }
    }
    while (!free_machines.empty()) {
        auto machine_id = free_machines.front();
        free_machines.pop();
        machine_traversal_order.push_back(machine_id);
        for (auto successor_id : successors[machine_id]) {
            predecessors[successor_id].erase(machine_id);
            if (predecessors[successor_id].empty()) {
                free_machines.push(successor_id);
            }
        }
    }
}

void Topology::buildPredecessorAndSuccessorMaps(
    std::map<long, std::set<long>>& predecessors,
    std::map<long, std::set<long>>& successors,
    TopologyElement* element,
    TopologyElement* parent
) {
    auto element_id = element->getId();
    if (parent) {
        auto parent_id = parent->getId();
        predecessors[element_id].insert(parent_id);
        successors[parent_id].insert(element_id);
    }

    switch (element->getGeneralTopologyElementType())
    {
    case ABSTRACT_GENERAL_TOPOLOGY_ELEMENT:
        throw SchedulingError("Abstract topology element encountered in Topology::buildPredecessorAndSuccessorMaps function.");

    case MACHINE_GENERAL_TOPOLOGY_ELEMENT:
        break;

    case GROUP_GENERAL_TOPOLOGY_ELEMENT:
        auto group = dynamic_cast<Group*>(element);
        for (auto child : group->getChildren()) {
            buildPredecessorAndSuccessorMaps(predecessors, successors, child, element);
        }
        break;
    }
}

long Topology::getPriorityValue(long const machine_id_1, long const machine_id_2) {
    return priority_map[machine_id_1][machine_id_2];
}