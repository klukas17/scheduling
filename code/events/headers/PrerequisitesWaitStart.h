//
// Created by mihael on 9/2/23.
//

#ifndef SCHEDULING_PREREQUISITESWAITSTART_H
#define SCHEDULING_PREREQUISITESWAITSTART_H

#include "JobAndMachineEvent.h"

class PrerequisitesWaitStart final : public JobAndMachineEvent {
public:
    PrerequisitesWaitStart(double time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_PREREQUISITESWAITSTART_H
