//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineBufferElement.cpp
 * @brief Implements the member functions of the MachineBufferElement class.
 */

#include "MachineBufferElement.h"

MachineBufferElement::MachineBufferElement(long step_id, long job_id, long time_start_processing, long time_remaining_processing, bool preempt) {
    this->step_id = step_id;
    this->job_id = job_id;
    this->time_start_processing = time_start_processing;
    this->time_remaining_processing = time_remaining_processing;
    this->preempt = preempt;
    this->prev = nullptr;
    this->next = nullptr;
}