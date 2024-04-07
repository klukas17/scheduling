//
// Created by mihael on 30/06/23.
//

#include "MachineTypeMap.h"
#include "SchedulingError.h"
#include "ranges"

MachineTypeMap::MachineTypeMap() = default;

std::map<long, MachineType*> MachineTypeMap::getMachineTypeMap() {
    return machine_type_map;
}

MachineType* MachineTypeMap::getMachineType(long const machine_type_id) {
    if (!machine_type_map.contains(machine_type_id)) {
        return nullptr;
    }
    return machine_type_map[machine_type_id];
}

void MachineTypeMap::addMachineType(long const machine_type_id, MachineType* machine_type) {
    if (machine_type_map.contains(machine_type_id)) {
        throw SchedulingError("MachineType of id " + std::to_string(machine_type_id) + " already exists in MachineTypeMap.");
    }
    machine_type_map[machine_type_id] = machine_type;
}

void MachineTypeMap::constructSetupAndBatchRules(JobTypeMap *job_type_map) const {
    for (auto& machine_type : machine_type_map | std::views::values) {
        machine_type->constructSetupAndBatchRules(job_type_map);
    }
}