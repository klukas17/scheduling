//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineBuffer.cpp
 * @brief Implements the member functions of the MachineBuffer class.
 */

#include "MachineBuffer.h"
#include "SchedulingError.h"

MachineBuffer::MachineBuffer(std::vector<long> preferred_processing_order) {
    this->head = nullptr;
    this->current = nullptr;
    for (int i = 0; i < preferred_processing_order.size(); i++) {
        step_index_to_processing_index[preferred_processing_order[i]] = i;
        processing_index_to_step_index[i] = preferred_processing_order[i];
        step_index_to_node[preferred_processing_order[i]] = nullptr;
    }
}

void MachineBuffer::addStepToBuffer(long step_id, long job_id, long time_start_processing, long time_remaining_processing, bool preempt) {

    auto new_job = new MachineBufferElement(step_id, job_id, time_start_processing, time_remaining_processing, preempt);
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

std::pair<long, long> MachineBuffer::startProcessingAStep() {

    if (current != nullptr) {
        throw SchedulingError("Trying to start executing a step but another is executing in function MachineBuffer::startProcessingAStep.");
    }

    if (head == nullptr) {
        throw SchedulingError("Trying to take a step from an empty buffer in function MachineBuffer::startProcessingAStep.");
    }

    long step_id = head->step_id;
    long job_id = head->job_id;
    current = head;
    head = head->next;
    return {step_id, job_id};
}

std::pair<long, long> MachineBuffer::peekAtFirstProcessingStep() {

    if (current != nullptr) {
        throw SchedulingError("Trying to peek at the first step but another is executing in function MachineBuffer::startProcessingAStep.");
    }

    if (head == nullptr) {
        throw SchedulingError("Trying to peek at a step from an empty buffer in function MachineBuffer::startProcessingAStep.");
    }

    return {head->step_id, head->job_id};
}

void MachineBuffer::finishProcessingAStep() {

    if (current != nullptr) {
        step_index_to_node[current->step_id] = nullptr;
        delete current;
        current = nullptr;
    }

    else {
        throw SchedulingError("Trying to finish an empty step in MachineBuffer::finishProcessingAStep.");
    }
}

std::tuple<long, long> MachineBuffer::removeFirstAndRetrieveIt() {
    if (head != nullptr) {
        step_index_to_node[head->step_id] = nullptr;
        long step_id = head->step_id;
        long job_id = head->job_id;
        auto tmp = head;
        head = head->next;
        delete tmp;
        return {step_id, job_id};
    }

    else {
        throw SchedulingError("Trying to remove an empty step in MachineBuffer::removeFirstAndRetrieveIt.");
    }
}

bool MachineBuffer::checkShouldPreempt() {

    if (!current) {
        throw SchedulingError("Trying to preempt an empty step in MachineBuffer::checkShouldPreempt.");
    }

    if (!current->preempt) {
        return false;
    }

    return step_index_to_processing_index[current->step_id] > step_index_to_processing_index[head->step_id];
}

std::tuple<long, long> MachineBuffer::getCurrentStepData() {
    return {current->job_id, current->step_id};
}

void MachineBuffer::addStepWaitingForPrerequisite(long step_id, long job_id, long time_start_processing, long time_remaining_processing, bool preempt) {
    steps_waiting_for_prerequisites[job_id] = {step_id, time_start_processing, time_remaining_processing, preempt};
}

void MachineBuffer::moveCurrentToBuffer(long time) {

    if (head == nullptr) {
        head = current;
    }

    else {

        long other_index = step_index_to_processing_index[current->step_id] - 1;
        while (other_index >= 0 && step_index_to_node[processing_index_to_step_index[other_index]] == nullptr) {
            other_index--;
        }

        if (other_index == -1) {
            current->next = head;
            head->prev = current;
            head = current;
        }

        else {
            MachineBufferElement* other = step_index_to_node[processing_index_to_step_index[other_index]];
            MachineBufferElement* other_next = other->next;
            if (other_next) {
                other_next->prev = current;
            }
            current->next = other_next;
            current->prev = other;
            other->next = current;
        }

    }

    current->time_remaining_processing -= time - current->time_start_processing;
    current->time_start_processing = -1;

    current = nullptr;
}

long MachineBuffer::getRemainingTimeForCurrent() {

    if (!current) {
        throw SchedulingError("Trying to start an empty step in MachineBuffer::getRemainingTimeForCurrent.");
    }

    return current->time_remaining_processing;
}

void MachineBuffer::setTimeStartedProcessingForCurrent(long time) {

    if (!current) {
        throw SchedulingError("Trying to start an empty step in MachineBuffer::setTimeStartedProcessingForCurrent.");
    }

    current->time_start_processing = time;
}

void MachineBuffer::moveStepFromWaitingToBuffer(long job_id) {
    addStepToBuffer(std::get<0>(steps_waiting_for_prerequisites[job_id]), job_id, std::get<1>(steps_waiting_for_prerequisites[job_id]), std::get<2>(steps_waiting_for_prerequisites[job_id]), std::get<3>(steps_waiting_for_prerequisites[job_id]));
    steps_waiting_for_prerequisites[job_id] = {};
}

bool MachineBuffer::hasReadyJobs() {
    return head != nullptr;
}

bool MachineBuffer::checkCanPreemptCurrent() {

    if (!current) {
        throw SchedulingError("Trying to preempt an empty step in MachineBuffer::checkCanPreemptCurrent.");
    }

    return current->preempt;
}

bool MachineBuffer::comparePrioritiesOfTwoSteps(long step_id1, long step_id2) {
    return step_index_to_processing_index[step_id1] < step_index_to_processing_index[step_id2];
}