//
// Created by mihael on 9/25/23.
//

/**
 * @file MachineSetupContext.cpp
 * @brief Implements the member functions of the MachineSetupContext class.
 */


#include "MachineSetupContext.h"

MachineSetupContext::MachineSetupContext() {
    this->setup = nullptr;
    this->last_job_type = nullptr;
}

Setup *MachineSetupContext::getSetup() {
    return setup;
}

void MachineSetupContext::setSetup(Setup *setup) {
    this->setup = setup;
}

JobType *MachineSetupContext::getLastJobType() {
    return last_job_type;
}

void MachineSetupContext::setLastJobType(JobType *last_job_type) {
    this->last_job_type = last_job_type;
}