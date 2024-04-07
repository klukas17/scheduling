//
// Created by mihael on 9/18/23.
//

#ifndef SCHEDULING_MACHINEEXITFORCED_H
#define SCHEDULING_MACHINEEXITFORCED_H

#include "JobAndMachineEvent.h"

class MachineExitForced final : public JobAndMachineEvent {
public:
    MachineExitForced(double time, long job_id, long machine_id, long step_id);
};


#endif //SCHEDULING_MACHINEEXITFORCED_H
