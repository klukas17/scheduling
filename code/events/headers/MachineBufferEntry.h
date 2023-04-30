//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINEBUFFERENTRY_H
#define SCHEDULING_MACHINEBUFFERENTRY_H

#include "Event.h"

class MachineBufferEntry : public Event {
private:
    long job_id;
    long machine_id;
public:
    MachineBufferEntry(long time, long job_id, long machine_id);
    [[nodiscard]] long getJobId() const;
    [[nodiscard]] long getMachineId() const;
};


#endif //SCHEDULING_MACHINEBUFFERENTRY_H
