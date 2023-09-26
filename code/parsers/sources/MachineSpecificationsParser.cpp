//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineSpecificationsParser.cpp
 * @brief Implements the member functions of the MachineSpecificationsParser class.
 */

#include "MachineSpecificationsParser.h"
#include "SchedulingError.h"
#include "yaml-cpp/yaml.h"

MachineTypeMap* MachineSpecificationsParser::parse(const std::string& path) {
    auto machine_type_map = new MachineTypeMap();

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node machines_node = doc["machines"];

    std::map<long, std::vector<std::tuple<long, long, long>>> all_setup_data;

    if (machines_node) {
        for (YAML::const_iterator it = machines_node.begin(); it != machines_node.end(); ++it) {
            std::vector<std::tuple<long, long, long>> machine_type_setup_data;
            if (!(*it)["machine_id"]) {
                throw SchedulingError("Entry in the 'machines' array must contain 'machine_id' field in the file " + path);
            }
            long id = (*it)["machine_id"].as<long>();
            long preempt = ((*it)["preempt"]) && (*it)["preempt"].as<bool>();
            YAML::Node setup_node = (*it)["setup"];
            std::vector<Setup*> setups;
            for (auto setup_it = setup_node.begin(); setup_it != setup_node.end(); setup_it++) {
                if (!(*setup_it)["time"]) {
                    throw SchedulingError("Entry in the 'setup' array must contain 'time' field in the file " + path);
                }
                long time = (*setup_it)["time"].as<long>();
                long from = ((*setup_it)["from"]) ? (*setup_it)["from"].as<long>() : -1;
                long to = ((*setup_it)["to"]) ? (*setup_it)["to"].as<long>() : -1;
                machine_type_setup_data.emplace_back(time, from, to);
            }
            auto machine_type = new MachineType(id, preempt, machine_type_setup_data);
            machine_type_map->addMachineType(id, machine_type);
            all_setup_data[id] = machine_type_setup_data;
        }
    } else {
        throw SchedulingError("'machines' key not found in the file " + path);
    }

    return machine_type_map;
}
