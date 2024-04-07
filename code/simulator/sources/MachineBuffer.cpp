//
// Created by mihael on 29/04/23.
//

#include "MachineBuffer.h"
#include "SchedulingError.h"
#include "ranges"

MachineBuffer::MachineBuffer(std::vector<long> const & preferred_processing_order) {
    this->head = nullptr;
    this->current = nullptr;
    for (int i = 0; i < preferred_processing_order.size(); i++) {
        step_index_to_processing_index[preferred_processing_order[i]] = i;
        processing_index_to_step_index[i] = preferred_processing_order[i];
        step_index_to_node[preferred_processing_order[i]] = nullptr;
    }
}

void MachineBuffer::addStepToBuffer(long const step_id, long const job_id, long const job_type_id, double const time_start_processing, double const time_remaining_processing, bool const preempt) {

    auto const new_job = new MachineBufferElement(step_id, job_id, job_type_id, time_start_processing, time_remaining_processing, preempt);
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

void MachineBuffer::startProcessingAStep() {

    if (current != nullptr) {
        throw SchedulingError("Trying to start executing a step but another is executing in function MachineBuffer::startProcessingAStep.");
    }

    if (head == nullptr) {
        throw SchedulingError("Trying to take a step from an empty buffer in function MachineBuffer::startProcessingAStep.");
    }

    current = head;
    head = head->next;
    if (current->next) {
        current->next->prev = nullptr;
    }
    current->prev = current->next = nullptr;
}

std::pair<long, long> MachineBuffer::peekAtFirstProcessingStep() const {

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

void MachineBuffer::finishProcessingAStepInBatch(long const job_id) {

    if (auto const current_in_batch = current_batch[job_id]; current_in_batch != nullptr) {
        current_batch[current_in_batch->job_id] = nullptr;
        delete current_in_batch;
    }

    else {
        throw SchedulingError("Trying to finish an empty step in MachineBuffer::finishProcessingAStepInBatch.");
    }
}


std::tuple<long, long> MachineBuffer::removeFirstAndRetrieveIt() {
    if (head != nullptr) {
        step_index_to_node[head->step_id] = nullptr;
        long step_id = head->step_id;
        long job_id = head->job_id;
        auto const tmp = head;
        head = head->next;
        delete tmp;
        return {step_id, job_id};
    }

    throw SchedulingError("Trying to remove an empty step in MachineBuffer::removeFirstAndRetrieveIt.");
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

std::tuple<long, long> MachineBuffer::getCurrentStepData() const {
    return {current->job_id, current->step_id};
}

std::vector<std::tuple<long, long> > MachineBuffer::getCurrentStepBatchData() const {
    std::vector<std::tuple<long, long>> current_step_batch_data;
    for (const auto& batch_step : current_batch | std::views::values) {
        if (batch_step != nullptr) {
            current_step_batch_data.emplace_back(batch_step->job_id, batch_step->step_id);
        }
    }
    return current_step_batch_data;
}

void MachineBuffer::addStepWaitingForPrerequisite(long step_id, long const job_id, long job_type_id, double time_start_processing, double time_remaining_processing, bool preempt) {
    steps_waiting_for_prerequisites[job_id] = {step_id, job_type_id, time_start_processing, time_remaining_processing, preempt};
}

void MachineBuffer::moveCurrentToBuffer(double const time) {

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

    step_index_to_node[current->step_id] = current;

    current = nullptr;
}

void MachineBuffer::moveCurrentInBatchToBuffer(double const time, long const job_id) {

    auto const current_in_batch = current_batch[job_id];
    current_batch[job_id] = nullptr;

    if (head == nullptr) {
        head = current_in_batch;
    }

    else {

        long other_index = step_index_to_processing_index[current_in_batch->step_id] - 1;
        while (other_index >= 0 && step_index_to_node[processing_index_to_step_index[other_index]] == nullptr) {
            other_index--;
        }

        if (other_index == -1) {
            current_in_batch->next = head;
            head->prev = current_in_batch;
            head = current_in_batch;
        }

        else {
            MachineBufferElement* other = step_index_to_node[processing_index_to_step_index[other_index]];
            MachineBufferElement* other_next = other->next;
            if (other_next) {
                other_next->prev = current_in_batch;
            }
            current_in_batch->next = other_next;
            current_in_batch->prev = other;
            other->next = current_in_batch;
        }

    }

    current_in_batch->time_remaining_processing -= time - current_in_batch->time_start_processing;
    current_in_batch->time_start_processing = -1;

    step_index_to_node[current_in_batch->step_id] = current_in_batch;
}

double MachineBuffer::getRemainingTimeForCurrent() const {

    if (!current) {
        throw SchedulingError("Trying to start an empty step in MachineBuffer::getRemainingTimeForCurrent.");
    }

    return current->time_remaining_processing;
}

double MachineBuffer::getRemainingTimeForCurrentInBatch(long const job_id) {
    auto const current_in_batch = current_batch[job_id];

    if (!current_in_batch) {
        throw SchedulingError("Trying to start an empty step in MachineBuffer::getRemainingTimeForCurrentInBatch.");
    }

    return current_in_batch->time_remaining_processing;
}

void MachineBuffer::setTimeStartedProcessingForCurrent(double const time) const {

    if (!current) {
        throw SchedulingError("Trying to start an empty step in MachineBuffer::setTimeStartedProcessingForCurrent.");
    }

    current->time_start_processing = time;
}

void MachineBuffer::setTimeStartedProcessingForCurrentInBatch(double const time, long const job_id) {

    auto const current_in_batch = current_batch[job_id];

    if (!current_in_batch) {
        throw SchedulingError("Trying to start an empty step in MachineBuffer::setTimeStartedProcessingForCurrentInBatch.");
    }

    current_in_batch->time_start_processing = time;
}


void MachineBuffer::moveStepFromWaitingToBuffer(long const job_id) {
    addStepToBuffer(
        std::get<0>(steps_waiting_for_prerequisites[job_id]),
        job_id,
        std::get<1>(steps_waiting_for_prerequisites[job_id]),
        std::get<2>(steps_waiting_for_prerequisites[job_id]),
        std::get<3>(steps_waiting_for_prerequisites[job_id]),
        std::get<4>(steps_waiting_for_prerequisites[job_id])
    );
    steps_waiting_for_prerequisites[job_id] = {};
}

bool MachineBuffer::hasReadyJobs() const {
    return head != nullptr;
}

bool MachineBuffer::checkCanPreemptCurrent() const {

    if (!current) {
        throw SchedulingError("Trying to preempt an empty step in MachineBuffer::checkCanPreemptCurrent.");
    }

    return current->preempt;
}

bool MachineBuffer::comparePrioritiesOfTwoSteps(long const step_id1, long const step_id2) {
    return step_index_to_processing_index[step_id1] < step_index_to_processing_index[step_id2];
}

std::vector<std::tuple<long, long> > MachineBuffer::startBatchProcessing(const BatchProcessingScenario *scenario) {
    auto const job_type_id = scenario->getJobType()->getId();
    auto const jobs_per_batch = scenario->getJobsPerBatch();

    auto jobs_in_batch = 1;
    auto curr = head;

    std::vector<std::tuple<long, long>> jobs_added_to_batch;

    while (curr && jobs_in_batch < jobs_per_batch) {
        if (curr->job_type_id != job_type_id || curr->time_remaining_processing != current->time_remaining_processing) {
            curr = curr->next;
            continue;
        }

        if (curr == head) {
            head = head->next;
            if (head) {
                head->prev = nullptr;
            }
        } else {
            auto const prev = head->prev;
            auto const next = head->next;
            if (prev) {
                prev->next = next;
            }
            if (next) {
                next->prev = prev;
            }
        }
        jobs_in_batch++;
        jobs_added_to_batch.emplace_back(curr->step_id, curr->job_id);
        current_batch[curr->job_id] = curr;
        step_index_to_node[curr->job_id] = nullptr;

        auto const tmp = curr;
        curr = curr->next;
        tmp->prev = tmp->next = nullptr;
    }

    return jobs_added_to_batch;
}
