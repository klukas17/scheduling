//
// Created by mihael on 10/1/23.
//

/**
 * @file MachineExitForcedBatch.cpp
 * @brief Implements the member functions of the MachineExitForcedBatch class.
 */

#include "MachineExitForcedBatch.h"

MachineExitForcedBatch::MachineExitForcedBatch(long time, long job_id, long machine_id, long step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = MACHINE_EXIT_FORCED_BATCH;
    this->message = "Job " + std::to_string(job_id) + ": Forcefully finished processing in a batch on Machine " + std::to_string(machine_id) + " (step_id = " + std::to_string(step_id) + ")";
}