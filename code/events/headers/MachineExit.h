//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_MACHINEEXIT_H
#define SCHEDULING_MACHINEEXIT_H

#include "JobEvent.h"
#include "MachineEvent.h"

class MachineExit : public JobEvent, public MachineEvent{
public:
    MachineExit(long time, long job_id, long machine_id);
};


#endif //SCHEDULING_MACHINEEXIT_H
