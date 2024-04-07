//
// Created by mihael on 10/1/23.
//

#ifndef SCHEDULING_PREEMPTBATCH_H
#define SCHEDULING_PREEMPTBATCH_H

#include "JobAndMachineEvent.h"

class PreemptBatch final : public JobAndMachineEvent {
public:
    PreemptBatch(double time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_PREEMPTBATCH_H
