//
// Created by mihael on 9/18/23.
//

#ifndef SCHEDULING_BREAKDOWNSTART_H
#define SCHEDULING_BREAKDOWNSTART_H

#include "MachineEvent.h"

class BreakdownStart final : public MachineEvent {
public:
    BreakdownStart(double time, long machine_id);
};


#endif //SCHEDULING_BREAKDOWNSTART_H
