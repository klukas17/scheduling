//
// Created by mihael on 5/9/24.
//

#include "RandomPathTopologyEnumerator.h"

#include "OpenGroup.h"
#include "ParallelGroup.h"
#include "RouteGroup.h"
#include "SerialGroup.h"
#include <climits>

RandomPathTopologyEnumerator::RandomPathTopologyEnumerator(Topology* topology, double change_element_chance) : TopologyEnumerator(topology) {
    this->change_element_chance = change_element_chance;
    this->chance_generator = new UniformRealDistributionGenerator(0, 1);
    this->choice_generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

std::set<long> RandomPathTopologyEnumerator::getPartition() {
    std::set<long> result;
    traverseTopology(result, topology->getRootElement());
    return result;
}

void RandomPathTopologyEnumerator::traverseTopology(std::set<long>& partition, TopologyElement* element) {
    partition.insert(element->getId());

    switch(element->getTopologyElementType()) {
        case ABSTRACT_TOPOLOGY_ELEMENT:
        case MACHINE_TOPOLOGY_ELEMENT:
            break;

        case SERIAL_GROUP_TOPOLOGY_ELEMENT: {}
            {
                for (auto child : dynamic_cast<SerialGroup*>(element)->getChildren()) {
                    traverseTopology(partition, child);
                }
                break;
            }

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
            {
                auto children = dynamic_cast<ParallelGroup*>(element)->getChildren();
                if (children.empty()) {
                    break;
                }
                auto child_index = choice_generator->generate() % children.size();
                traverseTopology(partition, children[child_index]);
                break;
            }

        case ROUTE_GROUP_TOPOLOGY_ELEMENT:
            {
                for (auto child : dynamic_cast<RouteGroup*>(element)->getChildren()) {
                    if (chance_generator->generate() < change_element_chance) {
                        traverseTopology(partition, child);
                    }
                }
                break;
            }

        case OPEN_GROUP_TOPOLOGY_ELEMENT:
            {
                for (auto child : dynamic_cast<OpenGroup*>(element)->getChildren()) {
                    if (chance_generator->generate() < change_element_chance) {
                        traverseTopology(partition, child);
                    }
                }
                break;
            }
    }
}

