//
// Created by mihael on 9/26/23.
//

#include "MachineBufferEntryRequestSynchronous.h"

MachineBufferEntryRequestSynchronous::MachineBufferEntryRequestSynchronous(double const time, long const job_id, long const machine_id, long const step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = MACHINE_BUFFER_ENTRY_REQUEST_SYNCHRONOUS;
}