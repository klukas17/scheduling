//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINETOPOLOGYPARSER_H
#define SCHEDULING_MACHINETOPOLOGYPARSER_H

#include "Topology.h"
#include "string"
#include "MachineTypeMap.h"
#include "yaml-cpp/yaml.h"
#include "set"

class MachineTopologyParser {
public:
    static Topology* parse(const std::string& path, MachineTypeMap* machine_type_map);
    static TopologyElement* parseElement(const std::string& path, const YAML::Node& node, MachineTypeMap* machine_type_map, std::set<long>& predecessor_ids, std::set<long>& successor_ids);
};

#endif // SCHEDULING_MACHINETOPOLOGYPARSER_H

