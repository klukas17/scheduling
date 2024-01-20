//
// Created by mihael on 10/1/23.
//

/**
 * @file MachineExitBatch.cpp
 * @brief Implements the member functions of the MachineExitBatch class.
 */

#include "MachineExitBatch.h"

MachineExitBatch::MachineExitBatch(long time, long job_id, long machine_id, long step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = MACHINE_EXIT_BATCH;
    this->message = "Job " + std::to_string(job_id) + ": Finished processing in a batch on Machine " + std::to_string(machine_id) + " (step_id = " + std::to_string(step_id) + ")";
}