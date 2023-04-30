//
// Created by mihael on 29/04/23.
//

#include <iostream>
#include "MachineSpecificationsParser.h"
#include "yaml-cpp/yaml.h"

MachineSpecificationsParser::MachineSpecificationsParser() = default;

std::map<long, MachineType*> MachineSpecificationsParser::parse(const std::string& path) {

    std::map<long, MachineType*> machine_type_map;

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node machines_node = doc["machines"];

    if (machines_node) {
        for (YAML::const_iterator it = machines_node.begin(); it != machines_node.end(); ++it) {
            const YAML::Node& machine_node = (*it)["machine"];
            long id = machine_node["id"].as<long>();
            auto machine_type = new MachineType(id);
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

