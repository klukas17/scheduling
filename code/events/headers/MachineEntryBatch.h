//
// Created by mihael on 10/1/23.
//

#ifndef SCHEDULING_MACHINEENTRYBATCH_H
#define SCHEDULING_MACHINEENTRYBATCH_H

#include "JobAndMachineEvent.h"

class MachineEntryBatch final: public JobAndMachineEvent {
public:
    MachineEntryBatch(double time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEENTRYBATCH_H
