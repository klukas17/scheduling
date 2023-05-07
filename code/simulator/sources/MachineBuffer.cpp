//
// Created by mihael on 29/04/23.
//

#include "MachineBuffer.h"

MachineBuffer::MachineBuffer(std::vector<long> preferred_processing_order) {
    this->head = nullptr;
    for (int i = 0; i < preferred_processing_order.size(); i++) {
        step_index_to_processing_index[preferred_processing_order[i]] = i;
        processing_index_to_step_index[i] = preferred_processing_order[i];
        step_index_to_node[preferred_processing_order[i]] = nullptr;
    }
}

void MachineBuffer::addStepToBuffer(long step_id, long job_id) {

    auto new_job = new MachineBufferElement(step_id, job_id);
    step_index_to_node[step_id] = new_job;

    if (head == nullptr) {
        head = new_job;
    }

    else {

        long other_index = step_index_to_processing_index[step_id] - 1;
        while (other_index >= 0 && step_index_to_node[processing_index_to_step_index[other_index]] == nullptr) {
            other_index--;
        }

        if (other_index == -1) {
            new_job->next = head;
            head->prev = new_job;
            head = new_job;
        }

        else {
            MachineBufferElement* other = step_index_to_node[processing_index_to_step_index[other_index]];
            MachineBufferElement* other_next = other->next;
            if (other_next) {
                other_next->prev = new_job;
            }
            new_job->next = other_next;
            new_job->prev = other;
            other->next = new_job;
        }

    }
}

std::pair<long, long> MachineBuffer::takeStepFromBuffer() {

    if (head != nullptr) {
        long step_id = head->step_id;
        long job_id = head->job_id;
        MachineBufferElement* old_head = head;
        head = head->next;
        delete old_head;
        return std::pair<long, long>{step_id, job_id};
    }

    else {
        // todo:error
    }
}