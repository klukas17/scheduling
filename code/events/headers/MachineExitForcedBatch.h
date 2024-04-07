//
// Created by mihael on 10/1/23.
//

#ifndef SCHEDULING_MACHINEEXITFORCEDBATCH_H
#define SCHEDULING_MACHINEEXITFORCEDBATCH_H

#include "JobAndMachineEvent.h"

class MachineExitForcedBatch final : public JobAndMachineEvent {
public:
    MachineExitForcedBatch(double time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEEXITFORCEDBATCH_H
