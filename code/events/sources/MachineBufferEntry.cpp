//
// Created by mihael on 29/04/23.
//

#include "MachineBufferEntry.h"

MachineBufferEntry::MachineBufferEntry(long time, long job_id, long machine_id, long step_id) : Event(time), JobEvent(time, job_id), MachineEvent(time, machine_id, step_id) {
    this->event_type = MACHINE_BUFFER_ENTRY;
    this->message = "Job " + std::to_string(job_id) + ": Machine " + std::to_string(machine_id) + " buffer entry" + " (step_id = " + std::to_string(step_id) + ")";
}