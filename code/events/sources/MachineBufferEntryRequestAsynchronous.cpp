//
// Created by mihael on 9/30/23.
//

/**
 * @file MachineBufferEntryRequestAsynchronous.cpp
 * @brief Implements the member functions of the MachineBufferEntryRequestAsynchronous class.
 */

#include "MachineBufferEntryRequestAsynchronous.h"

MachineBufferEntryRequestAsynchronous::MachineBufferEntryRequestAsynchronous(long time, long job_id, long machine_id, long step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = MACHINE_BUFFER_ENTRY_REQUEST_ASYNCHRONOUS;
}