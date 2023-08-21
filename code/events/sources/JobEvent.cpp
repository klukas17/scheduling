//
// Created by mihael on 30/04/23.
//

/**
 * @file JobEvent.cpp
 * @brief Implements the member functions of the JobEvent class.
 */

#include "JobEvent.h"

JobEvent::JobEvent(long time, long job_id) : Event(time) {
    this->job_id = job_id;
}

JobEvent::~JobEvent() = default;

long JobEvent::getJobId() const {
    return job_id;
}