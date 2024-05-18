//
// Created by mihael on 5/18/24.
//

#include "BreakdownsGenerator.h"

#include "Group.h"

void BreakdownsGenerator::generateBreakdowns(Topology* topology, TopologyBreakdownsGeneratorParameters* topology_parameters) {
    generateBreakdownsForMachine(topology->getRootElement(), topology_parameters);
}

void BreakdownsGenerator::generateBreakdownsForMachine(TopologyElement* topology_element, TopologyBreakdownsGeneratorParameters* topology_parameters) {

    auto breakdowns_generator = topology_parameters->getMachineParameters(topology_element->getId());

    if (breakdowns_generator != nullptr) {
        auto breakdown_count = breakdowns_generator->getNumberOfBreakdowns();
        double time = 0;
        for (int i = 0; i < breakdown_count; i++) {
            double start_time = time + breakdowns_generator->generateBreakdownStart();
            double end_time = start_time + breakdowns_generator->generateBreakdownDuration();
            topology_element->addBreakdown(new Breakdown(start_time, end_time));
            time = end_time;
        }
    }

    if (topology_element->getGeneralTopologyElementType() == GROUP_GENERAL_TOPOLOGY_ELEMENT) {
        for (auto child : dynamic_cast<Group*>(topology_element)->getChildren()) {
            generateBreakdownsForMachine(child, topology_parameters);
        }
    }
}
