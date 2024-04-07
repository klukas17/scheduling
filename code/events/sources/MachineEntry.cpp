//
// Created by mihael on 30/04/23.
//

#include "MachineEntry.h"

MachineEntry::MachineEntry(double const time, long const job_id, long const machine_id, long const step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = MACHINE_ENTRY;
    this->message = "Job " + std::to_string(job_id) + ": Started processing on Machine " + std::to_string(machine_id) + " (step_id = " + std::to_string(step_id) + ")";
}