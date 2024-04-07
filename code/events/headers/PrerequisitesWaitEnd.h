//
// Created by mihael on 9/2/23.
//

#ifndef SCHEDULING_PREREQUISITESWAITEND_H
#define SCHEDULING_PREREQUISITESWAITEND_H

#include "JobAndMachineEvent.h"

class PrerequisitesWaitEnd final : public JobAndMachineEvent {
public:
    PrerequisitesWaitEnd(double time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_PREREQUISITESWAITEND_H

