//
// Created by mihael on 9/30/23.
//

#ifndef SCHEDULING_MACHINEBUFFERENTRYREQUESTASYNCHRONOUS_H
#define SCHEDULING_MACHINEBUFFERENTRYREQUESTASYNCHRONOUS_H

#include "JobAndMachineEvent.h"

class MachineBufferEntryRequestAsynchronous final : public JobAndMachineEvent {
public:
    MachineBufferEntryRequestAsynchronous(double time, long job_id, long machine_id, long step_id);
};

#endif //SCHEDULING_MACHINEBUFFERENTRYREQUESTASYNCHRONOUS_H
