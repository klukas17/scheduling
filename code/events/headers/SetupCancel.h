//
// Created by mihael on 9/19/23.
//


#ifndef SCHEDULING_SETUPCANCEL_H
#define SCHEDULING_SETUPCANCEL_H

#include "JobAndMachineEvent.h"
#include "Setup.h"

class SetupCancel final : public JobAndMachineEvent {
    Setup* setup;
public:
    SetupCancel(double time, long job_id, long machine_id, long step_id, Setup* setup);
    [[nodiscard]] Setup* getSetup() const;
};

#endif //SCHEDULING_SETUPCANCEL_H

