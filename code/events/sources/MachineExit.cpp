//
// Created by mihael on 30/04/23.
//

#include "MachineExit.h"

MachineExit::MachineExit(long time, long job_id, long machine_id) : Event(time) {
    this->job_id = job_id;
    this->machine_id = machine_id;
    this->event_type = MACHINE_EXIT;
    this->message = "Job " + std::to_string(job_id) + ": Finished processing on Machine " + std::to_string(machine_id);
}

long MachineExit::getJobId() const {
    return job_id;
}

long MachineExit::getMachineId() const {
    return machine_id;
}