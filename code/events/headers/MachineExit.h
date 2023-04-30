//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_MACHINEEXIT_H
#define SCHEDULING_MACHINEEXIT_H

#include "Event.h"

class MachineExit : public Event {
private:
    long job_id;
    long machine_id;
public:
    MachineExit(long time, long job_id, long machine_id);
    [[nodiscard]] long getJobId() const;
    [[nodiscard]] long getMachineId() const;
};


#endif //SCHEDULING_MACHINEEXIT_H
