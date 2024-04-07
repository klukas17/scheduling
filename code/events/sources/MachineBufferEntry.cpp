//
// Created by mihael on 29/04/23.
//

#include "MachineBufferEntry.h"

MachineBufferEntry::MachineBufferEntry(double const time, long const job_id, long const machine_id, long const step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = MACHINE_BUFFER_ENTRY;
    this->message = "Job " + std::to_string(job_id) + ": Machine " + std::to_string(machine_id) + " buffer entry" + " (step_id = " + std::to_string(step_id) + ")";
}