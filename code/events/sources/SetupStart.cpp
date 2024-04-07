//
// Created by mihael on 9/19/23.
//

#include "SetupStart.h"

SetupStart::SetupStart(double const time, long const job_id, long const machine_id, long const step_id, Setup* setup) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = SETUP_START;
    auto const from = setup->getJobTypeFrom();
    auto const to = setup->getJobTypeTo();
    this->message = "Machine " + std::to_string(machine_id) + ": Started setup" +
                    (from ? " from a job of type " + std::to_string(from->getId()) : "") +
                    (to ? " to a job of type " + std::to_string(to->getId()) : "") +
                    " (step_id = " + std::to_string(step_id) + ")";
    this->setup = setup;
}

Setup *SetupStart::getSetup() const {
    return setup;
}