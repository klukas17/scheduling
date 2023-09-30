//
// Created by mihael on 9/26/23.
//

/**
 * @file MachineBufferEntryRequestSynchronous.cpp
 * @brief Implements the member functions of the MachineBufferEntryRequestSynchronous class.
 */

#include "MachineBufferEntryRequestSynchronous.h"

MachineBufferEntryRequestSynchronous::MachineBufferEntryRequestSynchronous(long time, long job_id, long machine_id, long step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = MACHINE_BUFFER_ENTRY_REQUEST_SYNCHRONOUS;
}