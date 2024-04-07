//
// Created by mihael on 8/21/23.
//

#include "JobAndMachineEvent.h"

JobAndMachineEvent::JobAndMachineEvent(double const time, long const job_id, long const machine_id, long const step_id) : Event(time), JobEvent(time, job_id), MachineEvent(time, machine_id) {
    this->step_id = step_id;
}

JobAndMachineEvent::~JobAndMachineEvent() = default;

long JobAndMachineEvent::getStepId() const {
    return step_id;
}