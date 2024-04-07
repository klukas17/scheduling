//
// Created by mihael on 9/19/23.
//

#ifndef SCHEDULING_SETUPSTART_H
#define SCHEDULING_SETUPSTART_H

#include "JobAndMachineEvent.h"
#include "Setup.h"

class SetupStart final : public JobAndMachineEvent {
    Setup* setup;
public:
    SetupStart(double time, long job_id, long machine_id, long step_id, Setup* setup);
    [[nodiscard]] Setup* getSetup() const;
};

#endif //SCHEDULING_SETUPSTART_H

