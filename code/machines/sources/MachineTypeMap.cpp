//
// Created by mihael on 30/06/23.
//

/**
 * @file MachineTypeMap.cpp
 * @brief Implements the member functions of the MachineTypeMap class.
 */

#include "MachineTypeMap.h"
#include "SchedulingError.h"

MachineTypeMap::MachineTypeMap() = default;

std::map<long, MachineType*> MachineTypeMap::getMachineTypeMap() {
    return machine_type_map;
}

MachineType* MachineTypeMap::getMachineType(long machine_type_id) {
    if (machine_type_map.find(machine_type_id) == machine_type_map.end()) {
        return nullptr;
    }
    return machine_type_map[machine_type_id];
}

void MachineTypeMap::addMachineType(long machine_type_id, MachineType* machine_type) {
    if (machine_type_map.find(machine_type_id) != machine_type_map.end()) {
        throw SchedulingError("MachineType of id " + std::to_string(machine_type_id) + " already exists in MachineTypeMap.");
    }
    machine_type_map[machine_type_id] = machine_type;
}

void MachineTypeMap::constructSetupRules(JobTypeMap *job_type_map) {
    for (auto entry : machine_type_map) {
        entry.second->constructSetupRules(job_type_map);
    }
}