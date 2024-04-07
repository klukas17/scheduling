//
// Created by mihael on 9/18/23.
//

#include "MachineExitForced.h"

MachineExitForced::MachineExitForced(double const time, long const job_id, long const machine_id, long const step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = MACHINE_EXIT_FORCED;
    this->message = "Job " + std::to_string(job_id) + ": Forcefully finished processing on Machine " + std::to_string(machine_id) + " (step_id = " + std::to_string(step_id) + ")";
}