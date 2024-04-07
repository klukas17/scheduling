//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_MACHINEEVENT_H
#define SCHEDULING_MACHINEEVENT_H

#include "Event.h"

class MachineEvent : public virtual Event {
protected:
    long machine_id;
public:
    MachineEvent(double time, long machine_id);
    ~MachineEvent() override = 0;
    [[nodiscard]] long getMachineId() const;
};

#endif //SCHEDULING_MACHINEEVENT_H
