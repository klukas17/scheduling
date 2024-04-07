//
// Created by mihael on 9/17/23.
//

#ifndef SCHEDULING_PREEMPT_H
#define SCHEDULING_PREEMPT_H

#include "JobAndMachineEvent.h"

class Preempt final : public JobAndMachineEvent {
public:
    Preempt(double time, long job_id, long machine_id, long step_id);
};


#endif //SCHEDULING_PREEMPT_H
