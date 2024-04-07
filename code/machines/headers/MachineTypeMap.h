//
// Created by mihael on 30/06/23.
//

#ifndef SCHEDULING_MACHINETYPEMAP_H
#define SCHEDULING_MACHINETYPEMAP_H

#include <map>
#include "MachineType.h"
#include "JobTypeMap.h"

class MachineTypeMap {
    std::map<long, MachineType*> machine_type_map;
public:
    MachineTypeMap();
    std::map<long, MachineType*> getMachineTypeMap();
    MachineType* getMachineType(long machine_type_id);
    void addMachineType(long machine_type_id, MachineType* machine_type);
    void constructSetupAndBatchRules(JobTypeMap* job_type_map) const;
};

#endif // SCHEDULING_MACHINETYPEMAP_H
