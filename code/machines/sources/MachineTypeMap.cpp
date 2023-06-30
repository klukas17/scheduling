//
// Created by mihael on 30/06/23.
//

/**
 * @file MachineTypeMap.cpp
 * @brief Implements the member functions of the MachineTypeMap class
 */

#include "MachineTypeMap.h"
#include "SchedulingError.h"

/**
 * @brief Constructs an empty MachineTypeMap object
 */
MachineTypeMap::MachineTypeMap() = default;

/**
 * @brief Gets the map of machine types
 * @return The map of machine types with their IDs as keys
 */
std::map<long, MachineType*> MachineTypeMap::getMachineTypeMap() {
    return machine_type_map;
}

/**
 * @brief Gets the machine type with the specified ID
 * @param machine_type_id The ID of the machine type to retrieve
 * @return A pointer to the MachineType object, or nullptr if not found
 */
MachineType* MachineTypeMap::getMachineType(long machine_type_id) {
    if (machine_type_map.find(machine_type_id) == machine_type_map.end()) {
        return nullptr;
    }
    return machine_type_map[machine_type_id];
}

/**
 * @brief Adds a machine type to the map
 * @param machine_type_id The ID of the machine type to add
 * @param machine_type A pointer to the MachineType object to add
 * @throw SchedulingError if a machine type with the same ID already exists in the map
 */
void MachineTypeMap::addMachineType(long machine_type_id, MachineType* machine_type) {
    if (machine_type_map.find(machine_type_id) != machine_type_map.end()) {
        throw SchedulingError("MachineType of id " + std::to_string(machine_type_id) + " already exists in MachineTypeMap.");
    }
    machine_type_map[machine_type_id] = machine_type;
}
