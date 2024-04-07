//
// Created by mihael on 9/19/23.
//

#ifndef SCHEDULING_SETUPEND_H
#define SCHEDULING_SETUPEND_H

#include "JobAndMachineEvent.h"
#include "Setup.h"

class SetupEnd final : public JobAndMachineEvent {
    Setup* setup;

public:
    SetupEnd(double time, long job_id, long machine_id, long step_id, Setup* setup);
    [[nodiscard]] Setup* getSetup() const;
};

#endif //SCHEDULING_SETUPEND_H

