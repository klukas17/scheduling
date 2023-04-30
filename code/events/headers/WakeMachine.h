//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_WAKEMACHINE_H
#define SCHEDULING_WAKEMACHINE_H

#include "Event.h"

class WakeMachine : public Event {
private:
    long machine_id;
public:
    WakeMachine(long time, long machine_id);
    [[nodiscard]] long getMachineId() const;
};


#endif //SCHEDULING_WAKEMACHINE_H
