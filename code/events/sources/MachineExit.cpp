//
// Created by mihael on 30/04/23.
//

#include "MachineExit.h"

MachineExit::MachineExit(double const time, long const job_id, long const machine_id, long const step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = MACHINE_EXIT;
    this->message = "Job " + std::to_string(job_id) + ": Finished processing on Machine " + std::to_string(machine_id) + " (step_id = " + std::to_string(step_id) + ")";
}