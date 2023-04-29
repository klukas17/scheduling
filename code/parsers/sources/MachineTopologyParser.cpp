//
// Created by mihael on 29/04/23.
//

#include <iostream>
#include "MachineTopologyParser.h"
#include "Machine.h"
#include "yaml-cpp/yaml.h"

MachineTopologyParser::MachineTopologyParser() {}

Topology *MachineTopologyParser::parse(std::string path, std::map<long, MachineType *> machine_type_map) {

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node topology_node = doc["topology"];

    if (topology_node) {

        long id = topology_node["machine"]["id"].as<long>();
        MachineType* machine_type = machine_type_map[topology_node["machine"]["machine_type_id"].as<long>()];

        TopologyElement* topology_element = new Machine(id, machine_type);
        Topology* topology = new Topology(topology_element);

        return topology;
    }

    else {
        // todo:error
        std::cerr << "Error: 'topology' node not found in " << path << " file." << std::endl;
        exit(1);
    }
}