//
// Created by mihael on 9/18/23.
//

#ifndef SCHEDULING_BREAKDOWNEND_H
#define SCHEDULING_BREAKDOWNEND_H

#include "MachineEvent.h"

class BreakdownEnd final : public MachineEvent {
public:
    BreakdownEnd(double time, long machine_id);
};


#endif //SCHEDULING_BREAKDOWNEND_H
