//
// Created by mihael on 29/04/23.
//

#include "MachineBufferElement.h"

MachineBufferElement::MachineBufferElement(long step_id, long job_id) {
    this->step_id = step_id;
    this->job_id = job_id;
    this->prev = nullptr;
    this->next = nullptr;
}