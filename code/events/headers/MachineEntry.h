//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_MACHINEENTRY_H
#define SCHEDULING_MACHINEENTRY_H

#include "Event.h"

class MachineEntry : public Event {
private:
    long job_id;
    long machine_id;
public:
    MachineEntry(long time, long job_id, long machine_id);
    long getJobId();
    long getMachineId();
};


#endif //SCHEDULING_MACHINEENTRY_H