//
// Created by mihael on 29/04/23.
//

#include <iostream>
#include "MachineSpecificationsParser.h"
#include "yaml-cpp/yaml.h"

MachineSpecificationsParser::MachineSpecificationsParser() {}

std::map<long, MachineType*> MachineSpecificationsParser::parse(std::string path) {

    std::map<long, MachineType*> machine_type_map;

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node machinesNode = doc["machines"];

    if (machinesNode) {
        for (YAML::const_iterator it = machinesNode.begin(); it != machinesNode.end(); ++it) {
            const YAML::Node& machineNode = (*it)["machine"];
            long id = machineNode["id"].as<long>();
            MachineType* machine_type = new MachineType(id);
            machine_type_map[id] = machine_type;
        }
    }

    else {
        // todo:error
        std::cerr << "Error: 'machines' node not found in " << path << " file." << std::endl;
        exit(1);
    }

    return machine_type_map;
}

