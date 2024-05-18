//
// Created by mihael on 5/18/24.
//

#ifndef BREAKDOWNSGENERATOR_H
#define BREAKDOWNSGENERATOR_H
#include "Topology.h"
#include "TopologyBreakdownsGeneratorParameters.h"


class BreakdownsGenerator {
public:
    static void generateBreakdowns(Topology* topology, TopologyBreakdownsGeneratorParameters* topology_parameters);
    static void generateBreakdownsForMachine(TopologyElement* topology_element, TopologyBreakdownsGeneratorParameters* topology_parameters);
};



#endif //BREAKDOWNSGENERATOR_H
