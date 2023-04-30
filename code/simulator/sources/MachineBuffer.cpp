//
// Created by mihael on 29/04/23.
//

#include "MachineBuffer.h"

MachineBuffer::MachineBuffer(std::vector<long> preferred_processing_order) {
    this->head = nullptr;
    this->preferred_processing_order = preferred_processing_order;
    for (int i = 0; i < preferred_processing_order.size(); i++) {
        job_index_to_processing_index[preferred_processing_order[i]] = i;
        processing_index_to_job_index[i] = preferred_processing_order[i];
        job_index_to_node[preferred_processing_order[i]] = nullptr;
    }
}

void MachineBuffer::addJobToBuffer(long job_id) {

    MachineBufferElement* new_job = new MachineBufferElement(job_id);
    job_index_to_node[job_id] = new_job;

    if (head == nullptr) {
        head = new_job;
    }

    else {

        long other_index = job_index_to_processing_index[job_id] - 1;
        while (other_index >= 0 && job_index_to_node[processing_index_to_job_index[other_index]] == nullptr) {
            other_index--;
        }

        if (other_index == -1) {
            new_job->next = head;
            head->prev = new_job;
            head = new_job;
        }

        else {
            MachineBufferElement* other = job_index_to_node[processing_index_to_job_index[other_index]];
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

long MachineBuffer::takeJobFromBuffer() {

    if (head != nullptr) {
        long job_id = head->job_id;
        MachineBufferElement* old_head = head;
        head = head->next;
        delete old_head;
        return job_id;
    }

    else {
        // todo:error
    }
}