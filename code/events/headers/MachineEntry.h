//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_MACHINEENTRY_H
#define SCHEDULING_MACHINEENTRY_H

#include "JobEvent.h"
#include "MachineEvent.h"

class MachineEntry : public JobEvent, public MachineEvent {
public:
    MachineEntry(long time, long job_id, long machine_id, long step_id);
};


#endif //SCHEDULING_MACHINEENTRY_H
