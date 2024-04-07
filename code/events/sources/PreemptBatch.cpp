//
// Created by mihael on 10/1/23.
//

#include "PreemptBatch.h"

PreemptBatch::PreemptBatch(double const time, long const job_id, long const machine_id, long const step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = PREEMPT_BATCH;
    this->message = "Job " + std::to_string(job_id) + ": Preempted in a batch on Machine " + std::to_string(machine_id) + " (step_id = " + std::to_string(step_id) + ")";
}