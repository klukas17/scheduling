//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINEBUFFERENTRY_H
#define SCHEDULING_MACHINEBUFFERENTRY_H

#include "JobAndMachineEvent.h"

class MachineBufferEntry final : public JobAndMachineEvent {
public:
    MachineBufferEntry(double time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEBUFFERENTRY_H
