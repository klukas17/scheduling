//
// Created by mihael on 5/18/24.
//

#include "TopologyBreakdownsGeneratorParameters.h"
#include <utility>

TopologyBreakdownsGeneratorParameters::TopologyBreakdownsGeneratorParameters(std::map<long, MachineBreakdownsGeneratorParameters*> parameters_map) {
    this->parameters_map = std::move(parameters_map);
}

MachineBreakdownsGeneratorParameters* TopologyBreakdownsGeneratorParameters::getMachineParameters(long machine_id) {
    return parameters_map[machine_id];
}

