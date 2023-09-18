//
// Created by mihael on 9/18/23.
//

/**
 * @file MachineExitForced.cpp
 * @brief Implements the member functions of the MachineExitForced class.
 */

#include "MachineExitForced.h"

MachineExitForced::MachineExitForced(long time, long job_id, long machine_id, long step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = MACHINE_EXIT_FORCED;
    this->message = "Job " + std::to_string(job_id) + ": Forcefully finished processing on Machine " + std::to_string(machine_id) + " (step_id = " + std::to_string(step_id) + ")";
}