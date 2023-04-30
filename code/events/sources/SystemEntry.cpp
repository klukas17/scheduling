//
// Created by mihael on 29/04/23.
//

#include "SystemEntry.h"

SystemEntry::SystemEntry(long time, long job_id) : Event(time), JobEvent(time, job_id) {
    this->event_type = SYSTEM_ENTRY;
    this->message = "Job " + std::to_string(job_id) + ": System entry";
}