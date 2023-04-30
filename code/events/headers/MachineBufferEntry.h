//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINEBUFFERENTRY_H
#define SCHEDULING_MACHINEBUFFERENTRY_H

#include "JobEvent.h"
#include "MachineEvent.h"

class MachineBufferEntry : public JobEvent, public MachineEvent {
public:
    MachineBufferEntry(long time, long job_id, long machine_id);
};


#endif //SCHEDULING_MACHINEBUFFERENTRY_H
