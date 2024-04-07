//
// Created by mihael on 9/17/23.
//

#include "Preempt.h"

Preempt::Preempt(double const time, long const job_id, long const machine_id, long const step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = PREEMPT;
    this->message = "Job " + std::to_string(job_id) + ": Preempted on Machine " + std::to_string(machine_id) + " (step_id = " + std::to_string(step_id) + ")";
}