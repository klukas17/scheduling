//
// Created by mihael on 9/25/23.
//

#ifndef SCHEDULING_MACHINESETUPCONTEXT_H
#define SCHEDULING_MACHINESETUPCONTEXT_H

#include "Setup.h"
#include "JobType.h"

class MachineSetupContext {
    Setup* setup;
    JobType* last_job_type;
public:
    MachineSetupContext();
    [[nodiscard]] Setup* getSetup() const;
    void setSetup(Setup* setup);
    [[nodiscard]] JobType* getLastJobType() const;
    void setLastJobType(JobType* last_job_type);
};

#endif // SCHEDULING_MACHINESETUPCONTEXT_H
