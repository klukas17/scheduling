//
// Created by mihael on 9/19/23.
//

/**
 * @file SetupEnd.cpp
 * @brief Implements the member functions of the SetupEnd class.
 */

#include "SetupEnd.h"

SetupEnd::SetupEnd(long time, long job_id, long machine_id, long step_id, Setup* setup) : Event(time), JobAndMachineEvent(time, job_id, machine_id, step_id) {
    this->event_type = SETUP_END;
    auto from = setup->getJobTypeFrom();
    auto to = setup->getJobTypeTo();
    this->message = "Machine " + std::to_string(machine_id) + ": Finished setup" +
                    (from ? " from a job of type " + std::to_string(from->getId()) : "") +
                    (to ? " to a job of type " + std::to_string(to->getId()) : "") +
                    " (step_id = " + std::to_string(step_id) + ")";
    this->setup = setup;
}

Setup *SetupEnd::getSetup() {
    return setup;
}