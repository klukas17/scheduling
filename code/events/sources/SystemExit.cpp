//
// Created by mihael on 29/04/23.
//

/**
 * @file SystemExit.cpp
 * @brief Implements the member functions of the SystemExit class.
 */

#include "SystemExit.h"

SystemExit::SystemExit(long time, long job_id) : Event(time), JobEvent(time, job_id) {
    this->event_type = SYSTEM_EXIT;
    this->message = "Job " + std::to_string(job_id) + ": System exit";
}