//
// Created by mihael on 9/17/23.
//

/**
 * @file Preempt.cpp
 * @brief Implements the member functions of the Preempt class.
 */

#include "Preempt.h"

Preempt::Preempt(long time, long job_id, long machine_id, long step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = PREEMPT;
    this->message = "Job " + std::to_string(job_id) + ": Preempted on Machine " + std::to_string(machine_id) + " (step_id = " + std::to_string(step_id) + ")";
}