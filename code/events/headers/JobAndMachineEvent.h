//
// Created by mihael on 8/21/23.
//

#ifndef SCHEDULING_JOBANDMACHINEEVENT_H
#define SCHEDULING_JOBANDMACHINEEVENT_H

#include "MachineEvent.h"
#include "JobEvent.h"

class JobAndMachineEvent : public JobEvent, public MachineEvent {
    long step_id;
public:
    JobAndMachineEvent(double time, long job_id, long machine_id, long step_id);
    ~JobAndMachineEvent() override = 0;
    [[nodiscard]] long getStepId() const;
};

#endif //SCHEDULING_JOBANDMACHINEEVENT_H
