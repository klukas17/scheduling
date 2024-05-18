//
// Created by mihael on 5/18/24.
//

#ifndef TOPOLOGYBREAKDOWNSGENERATORPARAMETERS_H
#define TOPOLOGYBREAKDOWNSGENERATORPARAMETERS_H
#include <map>

#include "MachineBreakdownsGeneratorParameters.h"


class TopologyBreakdownsGeneratorParameters {
    std::map<long, MachineBreakdownsGeneratorParameters*> parameters_map;
public:
    explicit TopologyBreakdownsGeneratorParameters(std::map<long, MachineBreakdownsGeneratorParameters*> parameters_map);
    MachineBreakdownsGeneratorParameters* getMachineParameters(long machine_id);
};



#endif //TOPOLOGYBREAKDOWNSGENERATORPARAMETERS_H
