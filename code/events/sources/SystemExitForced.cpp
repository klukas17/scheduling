//
// Created by mihael on 9/18/23.
//

/**
 * @file SystemExitForced.cpp
 * @brief Implements the member functions of the SystemExitForced class.
 */

#include "SystemExitForced.h"

SystemExitForced::SystemExitForced(long time, long job_id) : Event(time), JobEvent(time, job_id) {
    this->event_type = SYSTEM_EXIT_FORCED;
    this->message = "Job " + std::to_string(job_id) + ": Forced system exit";
}