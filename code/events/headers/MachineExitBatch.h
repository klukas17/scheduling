//
// Created by mihael on 10/1/23.
//

#ifndef SCHEDULING_MACHINEEXITBATCH_H
#define SCHEDULING_MACHINEEXITBATCH_H

#include "JobAndMachineEvent.h"

class MachineExitBatch final : public JobAndMachineEvent {
public:
    MachineExitBatch(double time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEEXITBATCH_H
