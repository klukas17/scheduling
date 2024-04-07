//
// Created by mihael on 9/2/23.
//

#include "PrerequisitesWaitEnd.h"

PrerequisitesWaitEnd::PrerequisitesWaitEnd(double const time, long const job_id, long const machine_id, long const step_id) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = PREREQUISITES_WAIT_END;
    this->message = "Job " + std::to_string(job_id) + ": Finished waiting for prerequisites on Machine " + std::to_string(machine_id) + " (step_id = " + std::to_string(step_id) + ")";
}