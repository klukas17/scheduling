//
// Created by mihael on 30/04/23.
//

#include "MachineEntry.h"

MachineEntry::MachineEntry(long time, long job_id, long machine_id) : Event(time) {
    this->job_id = job_id;
    this->machine_id = machine_id;
    this->event_type = MACHINE_ENTRY;
}

long MachineEntry::getJobId() const {
    return job_id;
}

long MachineEntry::getMachineId() const {
    return machine_id;
}