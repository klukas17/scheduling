//
// Created by mihael on 5/18/24.
//

#ifndef BREAKDOWNSGENERATORSERIALIZER_H
#define BREAKDOWNSGENERATORSERIALIZER_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "Topology.h"


class BreakdownsGeneratorSerializer {
public:
    static void serializeTopology(const std::string& path, Topology* topology);
    static void serializeTopologyElement(YAML::Emitter& out, TopologyElement* topology_element);
};



#endif //BREAKDOWNSGENERATORSERIALIZER_H
