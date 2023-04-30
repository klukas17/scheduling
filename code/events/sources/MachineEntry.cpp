//
// Created by mihael on 30/04/23.
//

#include "MachineEntry.h"

MachineEntry::MachineEntry(long time, long job_id, long machine_id) : Event(time), JobEvent(time, job_id), MachineEvent(time, machine_id) {
    this->event_type = MACHINE_ENTRY;
}