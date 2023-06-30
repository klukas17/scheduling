//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineSpecificationsParser.cpp
 * @brief Implements the member functions of the MachineSpecificationsParser class
 */

#include "MachineSpecificationsParser.h"
#include "SchedulingError.h"
#include "yaml-cpp/yaml.h"

/**
 * @brief Constructs a MachineSpecificationsParser object
 */
MachineSpecificationsParser::MachineSpecificationsParser() = default;

/**
 * @brief Parses the machine specifications from the specified file
 * @param path The path to the file containing machine specifications
 * @return A pointer to the MachineTypeMap object containing the parsed machine types
 * @throws SchedulingError if the 'machines' key is not found in the file or an entry in the 'machines' array is missing the 'machine_id' field.
 */
MachineTypeMap* MachineSpecificationsParser::parse(const std::string& path) {
    auto machine_type_map = new MachineTypeMap();

    YAML::Node doc = YAML::LoadFile(path);
    YAML::Node machines_node = doc["machines"];

    if (machines_node) {
        for (YAML::const_iterator it = machines_node.begin(); it != machines_node.end(); ++it) {
            if (!(*it)["machine_id"]) {
                throw SchedulingError("Entry in the 'machines' array must contain 'machine_id' field in the file " + path);
            }
            long id = (*it)["machine_id"].as<long>();
            auto machine_type = new MachineType(id);
            machine_type_map->addMachineType(id, machine_type);
        }
    } else {
        throw SchedulingError("'machines' key not found in the file " + path);
    }

    return machine_type_map;
}
