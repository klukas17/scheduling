//
// Created by mihael on 9/2/23.
//

/**
 * @file PrerequisitesWaitStart.cpp
 * @brief Implements the member functions of the PrerequisitesWaitStart class.
 */

#include "PrerequisitesWaitStart.h"

PrerequisitesWaitStart::PrerequisitesWaitStart(long time, long job_id, long machine_id, long step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = PREREQUISITES_WAIT_START;
    this->message = "Job " + std::to_string(job_id) + ": Started waiting for prerequisites on Machine " + std::to_string(machine_id) + " (step_id = " + std::to_string(step_id) + ")";
}