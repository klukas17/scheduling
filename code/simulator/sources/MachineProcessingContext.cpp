//
// Created by mihael on 29/04/23.
//

#include "MachineProcessingContext.h"

MachineProcessingContext::MachineProcessingContext(long const machine_id, Scheduler* scheduler, long const buffer_size) {
    this->machine_id = machine_id;
    this->scheduler = scheduler;
    this->machine_buffer = new MachineBuffer(machine_id, scheduler);
    this->machine_buffer_requests = new MachineBuffer(machine_id, scheduler);
    this->buffer_size = buffer_size;
    this->machine_setup_context = new MachineSetupContext();
    this->steps_in_buffer = 0;
    this->steps_in_buffer_requests = 0;
    this->currently_working = false;
    this->currently_in_breakdown = false;
    this->batch_processing_scenario = nullptr;
    this->batch_processing_started = true;
}

long MachineProcessingContext::getMachineId() const {
    return machine_id;
}

long MachineProcessingContext::getBufferSize() const {
    return buffer_size;
}

void MachineProcessingContext::addStepToBuffer(long const step_id, long const job_id, long const job_type_id, double const time_start_processing, double const time_remaining_processing, bool const preempt) {
    machine_buffer->addStepToBuffer(step_id, job_id, job_type_id, time_start_processing, time_remaining_processing, preempt);
    steps_in_buffer++;
}

void MachineProcessingContext::addStepToBufferRequests(long const step_id, long const job_id, long const job_type_id, double const time_start_processing, double const time_remaining_processing, bool const preempt) {
    machine_buffer_requests->addStepToBuffer(step_id, job_id, job_type_id, time_start_processing, time_remaining_processing, preempt);
    steps_in_buffer_requests++;
}

long MachineProcessingContext::getStepsInBufferRequests() const {
    return steps_in_buffer_requests;
}

std::tuple<long, long> MachineProcessingContext::removeStepFromBufferRequests() {
    auto [step_id, job_id] = machine_buffer_requests->removeFirstAndRetrieveIt();
    steps_in_buffer_requests--;
    return {step_id, job_id};
}

bool MachineProcessingContext::bufferHasSpace() const {
    return buffer_size > steps_in_buffer;
}

void MachineProcessingContext::addStepWaitingForPrerequisite(long const step_id, long const job_id, long const job_type_id, double const time_start_processing, double const time_remaining_processing, bool const preempt) {
    machine_buffer->addStepWaitingForPrerequisite(step_id, job_id, job_type_id, time_start_processing, time_remaining_processing, preempt);
    steps_in_buffer++;
}

void MachineProcessingContext::moveStepFromWaitingToBuffer(long const job_id) const {
    machine_buffer->moveStepFromWaitingToBuffer(job_id);
}

void MachineProcessingContext::startProcessingAStep() const {
    machine_buffer->startProcessingAStep();
}

std::pair<long, long> MachineProcessingContext::peekAtFirstProcessingStep() const {
    return machine_buffer->peekAtFirstProcessingStep();
}

void MachineProcessingContext::finishProcessingAStep() {
    machine_buffer->finishProcessingAStep();
    currently_working = false;
}

void MachineProcessingContext::finishProcessingAStepInBatch(long const job_id) const {
    machine_buffer->finishProcessingAStepInBatch(job_id);
}

bool MachineProcessingContext::checkShouldPreempt() const {
    return machine_buffer->checkShouldPreempt();
}

std::tuple<long, long> MachineProcessingContext::getCurrentStepData() const {
    return machine_buffer->getCurrentStepData();
}

std::vector<std::tuple<long, long> > MachineProcessingContext::getCurrentStepBatchData() const {
    return machine_buffer->getCurrentStepBatchData();
}

void MachineProcessingContext::moveCurrentToBuffer(double const time) {
    machine_buffer->moveCurrentToBuffer(time);
    currently_working = false;
}

void MachineProcessingContext::moveCurrentInBatchToBuffer(double const time, long const job_id) const {
    machine_buffer->moveCurrentInBatchToBuffer(time, job_id);
}

double MachineProcessingContext::getRemainingTimeForCurrent() const {
    return machine_buffer->getRemainingTimeForCurrent();
}

double MachineProcessingContext::getRemainingTimeForCurrentInBatch(long const job_id) const {
    return machine_buffer->getRemainingTimeForCurrentInBatch(job_id);
}

void MachineProcessingContext::setTimeStartedProcessingForCurrent(double const time) const {
    machine_buffer->setTimeStartedProcessingForCurrent(time);
}

void MachineProcessingContext::setTimeStartedProcessingForCurrentInBatch(double const time, long const job_id) const {
    machine_buffer->setTimeStartedProcessingForCurrentInBatch(time, job_id);
}

long MachineProcessingContext::getStepsInBuffer() const {
    return steps_in_buffer;
}

void MachineProcessingContext::decreaseStepsInBuffer() {
    steps_in_buffer--;
}

bool MachineProcessingContext::getCurrentlyWorking() const {
    return currently_working;
}

void MachineProcessingContext::setCurrentlyWorking() {
    currently_working = true;
}

void MachineProcessingContext::unsetCurrentlyWorking() {
    currently_working = false;
}

bool MachineProcessingContext::hasReadyJobs() const {
    return machine_buffer->hasReadyJobs();
}

bool MachineProcessingContext::isInBreakdown() const {
    return currently_in_breakdown;
}

void MachineProcessingContext::setCurrentlyInBreakdown() {
    currently_in_breakdown = true;
}

void MachineProcessingContext::unsetCurrentlyInBreakdown() {
    currently_in_breakdown = false;
}

bool MachineProcessingContext::checkCanPreemptCurrent() const {
    return machine_buffer->checkCanPreemptCurrent();
}

Setup *MachineProcessingContext::getSetup() const {
    return machine_setup_context->getSetup();
}

void MachineProcessingContext::setSetup(Setup *setup) const {
    machine_setup_context->setSetup(setup);
}

JobType *MachineProcessingContext::getLastJobType() const {
    return machine_setup_context->getLastJobType();
}

void MachineProcessingContext::setLastJobType(JobType *last_job_type) const {
    machine_setup_context->setLastJobType(last_job_type);
}

bool MachineProcessingContext::comparePrioritiesOfTwoSteps(long const step_id1, long const step_id2) const {
    return machine_buffer->comparePrioritiesOfTwoSteps(step_id1, step_id2);
}

bool MachineProcessingContext::canAcceptAnotherJobInBuffer() const {
    return steps_in_buffer < buffer_size;
}

BatchProcessingScenario *MachineProcessingContext::getBatchProcessingScenario() const {
    return batch_processing_scenario;
}

void MachineProcessingContext::setBatchProcessingScenario(BatchProcessingScenario *scenario) {
    batch_processing_scenario = scenario;
    batch_processing_started = false;
}

void MachineProcessingContext::removeBatchProcessingScenario() {
    batch_processing_scenario = nullptr;
    batch_processing_started = true;
}

bool MachineProcessingContext::getBatchProcessingStarted() const {
    return batch_processing_started;
}

void MachineProcessingContext::setBatchProcessingStarted() {
    batch_processing_started = true;
}

std::vector<std::tuple<long, long> > MachineProcessingContext::startBatchProcessing() const {
    return machine_buffer->startBatchProcessing(batch_processing_scenario);
}

double MachineProcessingContext::getRemainingTimeProcessing(long job_id) {
    return machine_buffer->getRemainingTimeProcessing(job_id);
}
