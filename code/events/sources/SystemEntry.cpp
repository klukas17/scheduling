//
// Created by mihael on 29/04/23.
//

#include "../headers/SystemEntry.h"

SystemEntry::SystemEntry(long time, long job_id) : Event(time) {
    this->job_id = job_id;
    this->event_type = SYSTEM_ENTRY;
    this->message = "Job " + std::to_string(job_id) + ": System entry";
}

long SystemEntry::getJobId() const {
    return job_id;
}