//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_MACHINEENTRY_H
#define SCHEDULING_MACHINEENTRY_H

#include "JobAndMachineEvent.h"

class MachineEntry final : public JobAndMachineEvent {
public:
    MachineEntry(double time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEENTRY_H
