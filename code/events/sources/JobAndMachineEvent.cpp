//
// Created by mihael on 8/21/23.
//

/**
 * @file JobAndMachineEvent.cpp
 * @brief Implements the member functions of the JobAndMachineEvent class.
 */

#include "JobAndMachineEvent.h"

JobAndMachineEvent::JobAndMachineEvent(long time, long job_id, long machine_id, long step_id) : Event(time), JobEvent(time, job_id), MachineEvent(time, machine_id) {
    this->step_id = step_id;
}

JobAndMachineEvent::~JobAndMachineEvent() = default;

long JobAndMachineEvent::getStepId() const {
    return step_id;
}