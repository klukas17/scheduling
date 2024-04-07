//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_MACHINEEXIT_H
#define SCHEDULING_MACHINEEXIT_H

#include "JobAndMachineEvent.h"

class MachineExit final : public JobAndMachineEvent {
public:
    MachineExit(double time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEEXIT_H
