//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINETOPOLOGYPARSER_H
#define SCHEDULING_MACHINETOPOLOGYPARSER_H

#include "Topology.h"
#include "string"
#include "map"
#include "MachineType.h"
#include "yaml-cpp/yaml.h"
#include "set"

class MachineTopologyParser {
public:
    MachineTopologyParser();
    static Topology* parse(const std::string& path, const std::map<long, MachineType*>& machine_type_map);
    static TopologyElement* parseElement(const YAML::Node& node, const std::map<long, MachineType*>& machine_type_map, std::set<long>& predecessor_ids, std::set<long>& successor_ids);
};


#endif //SCHEDULING_MACHINETOPOLOGYPARSER_H
