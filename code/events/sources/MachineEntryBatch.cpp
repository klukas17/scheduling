//
// Created by mihael on 10/1/23.
//

/**
 * @file MachineEntryBatch.cpp
 * @brief Implements the member functions of the MachineEntryBatch class.
 */

#include "MachineEntryBatch.h"

MachineEntryBatch::MachineEntryBatch(long time, long job_id, long machine_id, long step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = MACHINE_ENTRY_BATCH;
    this->message = "Job " + std::to_string(job_id) + ": Started processing in a batch on Machine " + std::to_string(machine_id) + " (step_id = " + std::to_string(step_id) + ")";
}