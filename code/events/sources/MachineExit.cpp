//
// Created by mihael on 30/04/23.
//

#include "MachineExit.h"

MachineExit::MachineExit(long time, long job_id, long machine_id) : Event(time), JobEvent(time, job_id), MachineEvent(time, machine_id) {
    this->event_type = MACHINE_EXIT;
    this->message = "Job " + std::to_string(job_id) + ": Finished processing on Machine " + std::to_string(machine_id);
}