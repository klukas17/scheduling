//
// Created by mihael on 29/04/23.
//

#include "MachineBuffer.h"

#include "OfflineScheduler.h"
#include "SchedulingError.h"
#include "ranges"
#include <algorithm>

bool (*MachineBuffer::score_comparator)(MachineBufferElement*, MachineBufferElement*) =
    [](MachineBufferElement* a, MachineBufferElement* b) -> bool {
        if (a->score != b->score) {
            return a->score < b->score;
        }
        return a->job_id < b->job_id;
};

MachineBuffer::MachineBuffer(long machine_id, Scheduler* scheduler) {
    this->machine_id = machine_id;
    this->current = nullptr;
    this->scheduler = scheduler;
    this->changes_to_steps_made = false;
}

MachineBuffer::~MachineBuffer() {
    if (current) {
        delete current;
    }
    for (auto job_id : current_batch | std::views::keys) {
        delete current_batch[job_id];
    }
    for (int i = 0; i < queue.size(); i++) {
        delete queue[i];
    }
}

void MachineBuffer::addStepToBuffer(long const step_id, long const job_id, long const job_type_id, double const time_start_processing, double const time_remaining_processing, bool const preempt) {
    auto score = scheduler->calculateScore(machine_id, job_id, step_id);
    auto const new_step = new MachineBufferElement(step_id, job_id, job_type_id, time_start_processing, time_remaining_processing, preempt, score);
    remaining_time_processing_index[job_id] = time_remaining_processing;
    queue.push_back(new_step);
    std::push_heap(queue.begin(), queue.end(), score_comparator);
    changes_to_steps_made = true;
}

void MachineBuffer::startProcessingAStep() {

    if (current != nullptr) {
        throw SchedulingError("Trying to start executing a step but another is executing in function MachineBuffer::startProcessingAStep.");
    }

    if (queue.empty()) {
        throw SchedulingError("Trying to take a step from an empty buffer in function MachineBuffer::startProcessingAStep.");
    }

    if (changes_to_steps_made) {
        resetQueue();
    }

    std::pop_heap(queue.begin(), queue.end(), score_comparator);
    current = queue.back();
    queue.pop_back();
    changes_to_steps_made = true;
}

std::pair<long, long> MachineBuffer::peekAtFirstProcessingStep() {

    if (current != nullptr) {
        throw SchedulingError("Trying to peek at the first step but another is executing in function MachineBuffer::startProcessingAStep.");
    }

    if (queue.empty()) {
        throw SchedulingError("Trying to peek at a step from an empty buffer in function MachineBuffer::startProcessingAStep.");
    }

    if (changes_to_steps_made) {
        resetQueue();
    }

    auto const top = queue.front();

    return {top->step_id, top->job_id};
}

void MachineBuffer::finishProcessingAStep() {

    if (current != nullptr) {
        remaining_time_processing_index[current->job_id] = 0;
        changes_to_steps_made = true;
        delete current;
        current = nullptr;
    }

    else {
        throw SchedulingError("Trying to finish an empty step in MachineBuffer::finishProcessingAStep.");
    }
}

void MachineBuffer::finishProcessingAStepInBatch(long const job_id) {

    if (auto const current_in_batch = current_batch[job_id]; current_in_batch != nullptr) {
        current_batch.erase(current_in_batch->job_id);
        remaining_time_processing_index[current_in_batch->job_id] = 0;
        changes_to_steps_made = true;
        delete current_in_batch;
    }

    else {
        throw SchedulingError("Trying to finish an empty step in MachineBuffer::finishProcessingAStepInBatch.");
    }
}


std::tuple<long, long> MachineBuffer::removeFirstAndRetrieveIt() {
    if (!queue.empty()) {
        std::pop_heap(queue.begin(), queue.end(), score_comparator);
        auto const top = queue.back();
        queue.pop_back();
        changes_to_steps_made = true;
        long step_id = top->step_id;
        long job_id = top->job_id;
        delete top;
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

    return current->score < queue.front()->score;
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
    current->time_remaining_processing -= time - current->time_start_processing;
    remaining_time_processing_index[current->job_id] = current->time_remaining_processing;
    current->time_start_processing = -1;
    queue.push_back(current);
    std::push_heap(queue.begin(), queue.end(), score_comparator);
    current = nullptr;
    changes_to_steps_made = true;
}

void MachineBuffer::moveCurrentInBatchToBuffer(double const time, long const job_id) {
    auto const current_in_batch = current_batch[job_id];
    current_batch.erase(job_id);
    current_in_batch->time_remaining_processing -= time - current_in_batch->time_start_processing;
    remaining_time_processing_index[current_in_batch->job_id] = current_in_batch->time_remaining_processing;
    current_in_batch->time_start_processing = -1;
    queue.push_back(current_in_batch);
    std::push_heap(queue.begin(), queue.end(), score_comparator);
    changes_to_steps_made = true;
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
    changes_to_steps_made = true;
}

bool MachineBuffer::hasReadyJobs() const {
    return !queue.empty();
}

bool MachineBuffer::checkCanPreemptCurrent() const {

    if (!current) {
        throw SchedulingError("Trying to preempt an empty step in MachineBuffer::checkCanPreemptCurrent.");
    }

    return current->preempt;
}

bool MachineBuffer::comparePrioritiesOfTwoSteps(long const step_id1, long const step_id2) {
    return scheduler->comparePrioritiesOfTwoSteps(machine_id, step_id1, step_id2);
}

std::vector<std::tuple<long, long> > MachineBuffer::startBatchProcessing(const BatchProcessingScenario *scenario) {
    auto const job_type_id = scenario->getJobType()->getId();
    auto const jobs_per_batch = scenario->getJobsPerBatch();

    auto jobs_in_batch = 1;

    std::vector<std::tuple<long, long>> jobs_added_to_batch;
    std::vector<MachineBufferElement*> removed;

    while (!queue.empty() && jobs_in_batch < jobs_per_batch) {

        std::pop_heap(queue.begin(), queue.end(), score_comparator);
        auto top = queue.back();
        queue.pop_back();

        if (top->job_type_id != job_type_id || top->time_remaining_processing != current->time_remaining_processing) {
            removed.push_back(top);
            continue;
        }

        jobs_in_batch++;
        jobs_added_to_batch.emplace_back(top->step_id, top->job_id);
        current_batch[top->job_id] = top;
    }

    for (auto element : removed) {
        queue.push_back(element);
    }

    changes_to_steps_made = true;

    return jobs_added_to_batch;
}

double MachineBuffer::getRemainingTimeProcessing(long job_id) {
    return remaining_time_processing_index[job_id];
}

void MachineBuffer::resetQueue() {
    changes_to_steps_made = false;
    for (auto element : queue) {
        element->score = scheduler->calculateScore(machine_id, element->job_id, element->step_id);
    }
    std::make_heap(queue.begin(), queue.end(), score_comparator);
}
