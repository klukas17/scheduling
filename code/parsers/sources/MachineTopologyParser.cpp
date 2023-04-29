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
    YAML::Node topologyNode = doc["topology"];

    if (topologyNode) {

        //TopologyElement* topologyElement = new Machine(topologyNode["machine"]["id"])

        long id = topologyNode["machine"]["id"].as<long>();
        MachineType* machineType = machine_type_map[topologyNode["machine"]["machine_type_id"].as<long>()];

        TopologyElement* topologyElement = new Machine(id, machineType);
        Topology* topology = new Topology(topologyElement);

        return topology;
    }

    else {
        // todo:error
        std::cerr << "Error: 'topology' node not found in " << path << " file." << std::endl;
        exit(1);
    }
}