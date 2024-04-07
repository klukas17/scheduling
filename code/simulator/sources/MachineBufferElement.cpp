//
// Created by mihael on 29/04/23.
//

#include "MachineBufferElement.h"

MachineBufferElement::MachineBufferElement(long const step_id, long const job_id, long const job_type_id, double const time_start_processing, double const time_remaining_processing, bool const preempt) {
    this->step_id = step_id;
    this->job_id = job_id;
    this->job_type_id = job_type_id;
    this->time_start_processing = time_start_processing;
    this->time_remaining_processing = time_remaining_processing;
    this->preempt = preempt;
    this->prev = nullptr;
    this->next = nullptr;
}