//
// Created by mihael on 9/26/23.
//

#ifndef SCHEDULING_MACHINEBUFFERENTRYREQUESTSYNCHRONOUS_H
#define SCHEDULING_MACHINEBUFFERENTRYREQUESTSYNCHRONOUS_H

#include "JobAndMachineEvent.h"

class MachineBufferEntryRequestSynchronous final : public JobAndMachineEvent {
public:
    MachineBufferEntryRequestSynchronous(double time, long job_id, long machine_id, long step_id);
};


#endif //SCHEDULING_MACHINEBUFFERENTRYREQUESTSYNCHRONOUS_H
