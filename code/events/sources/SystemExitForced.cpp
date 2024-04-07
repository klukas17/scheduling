//
// Created by mihael on 9/18/23.
//

#include "SystemExitForced.h"

SystemExitForced::SystemExitForced(double const time, long const job_id) : Event(time), JobEvent(time, job_id) {
    this->event_type = SYSTEM_EXIT_FORCED;
    this->message = "Job " + std::to_string(job_id) + ": Forced system exit";
}