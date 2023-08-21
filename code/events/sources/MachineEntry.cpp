//
// Created by mihael on 30/04/23.
//

/**
 * @file MachineEntry.cpp
 * @brief Implements the member functions of the MachineEntry class.
 */

#include "MachineEntry.h"

MachineEntry::MachineEntry(long time, long job_id, long machine_id, long step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = MACHINE_ENTRY;
}