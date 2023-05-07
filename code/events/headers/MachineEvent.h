//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_MACHINEEVENT_H
#define SCHEDULING_MACHINEEVENT_H

#include "Event.h"

class MachineEvent : public virtual Event {
protected:
    long machine_id;
    long step_id;
public:
    MachineEvent(long time, long machine_id, long step_id);
    ~MachineEvent() override = 0;
    [[nodiscard]] long getMachineId() const;
    [[nodiscard]] long getStepId() const;
};


#endif //SCHEDULING_MACHINEEVENT_H
