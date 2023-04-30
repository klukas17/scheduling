//
// Created by mihael on 29/04/23.
//

#include "../headers/SystemExit.h"

SystemExit::SystemExit(long time, long job_id) : Event(time) {
    this->job_id = job_id;
    this->event_type = SYSTEM_EXIT;
    this->message = "Job " + std::to_string(job_id) + ": System exit";

}

long SystemExit::getJobId() const {
    return job_id;
}