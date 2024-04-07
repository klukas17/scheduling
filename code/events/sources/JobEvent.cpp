//
// Created by mihael on 30/04/23.
//

#include "JobEvent.h"

JobEvent::JobEvent(double const time, long const job_id) : Event(time) {
    this->job_id = job_id;
}

JobEvent::~JobEvent() = default;

long JobEvent::getJobId() const {
    return job_id;
}