//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineProcessingContext.cpp
 * @brief Implements the member functions of the MachineProcessingContext class.
 */

#include "MachineProcessingContext.h"

MachineProcessingContext::MachineProcessingContext(GenotypeNode *node) {
    this->node = node;
    this->machine_buffer = new MachineBuffer(node->getStepProcessingOrder());
    this->machine_setup_context = new MachineSetupContext();
    this->steps_in_buffer = 0;
    this->currently_working = false;
    this->currently_in_breakdown = false;
}

GenotypeNode *MachineProcessingContext::getNode() {
    return node;
}

void MachineProcessingContext::addStepToBuffer(long step_id, long job_id, long time_start_processing, long time_remaining_processing, bool preempt) {
    machine_buffer->addStepToBuffer(step_id, job_id, time_start_processing, time_remaining_processing, preempt);
    steps_in_buffer++;
}

void MachineProcessingContext::addStepWaitingForPrerequisite(long step_id, long job_id, long time_start_processing, long time_remaining_processing, bool preempt) {
    machine_buffer->addStepWaitingForPrerequisite(step_id, job_id, time_start_processing, time_remaining_processing, preempt);
    steps_in_buffer++;
}

void MachineProcessingContext::moveStepFromWaitingToBuffer(long job_id) {
    machine_buffer->moveStepFromWaitingToBuffer(job_id);
}

std::pair<long, long> MachineProcessingContext::startProcessingAStep() {
    return machine_buffer->startProcessingAStep();
}

std::pair<long, long> MachineProcessingContext::peekAtFirstProcessingStep() {
    return machine_buffer->peekAtFirstProcessingStep();
}

void MachineProcessingContext::finishProcessingAStep() {
    machine_buffer->finishProcessingAStep();
    steps_in_buffer--;
    currently_working = false;
}

bool MachineProcessingContext::checkShouldPreempt() {
    return machine_buffer->checkShouldPreempt();
}

std::tuple<long, long> MachineProcessingContext::getCurrentStepData() {
    return machine_buffer->getCurrentStepData();
}

void MachineProcessingContext::moveCurrentToBuffer(long time) {
    machine_buffer->moveCurrentToBuffer(time);
    currently_working = false;
}

long MachineProcessingContext::getRemainingTimeForCurrent() {
    return machine_buffer->getRemainingTimeForCurrent();
}

void MachineProcessingContext::setTimeStartedProcessingForCurrent(long time) {
    machine_buffer->setTimeStartedProcessingForCurrent(time);
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

bool MachineProcessingContext::hasReadyJobs() {
    return machine_buffer->hasReadyJobs();
}

bool MachineProcessingContext::isInBreakdown() {
    return currently_in_breakdown;
}

void MachineProcessingContext::setCurrentlyInBreakdown() {
    currently_in_breakdown = true;
}

void MachineProcessingContext::unsetCurrentlyInBreakdown() {
    currently_in_breakdown = false;
}

bool MachineProcessingContext::checkCanPreemptCurrent() {
    return machine_buffer->checkCanPreemptCurrent();
}

Setup *MachineProcessingContext::getSetup() {
    return machine_setup_context->getSetup();
}

void MachineProcessingContext::setSetup(Setup *setup) {
    machine_setup_context->setSetup(setup);
}

JobType *MachineProcessingContext::getLastJobType() {
    return machine_setup_context->getLastJobType();
}

void MachineProcessingContext::setLastJobType(JobType *last_job_type) {
    machine_setup_context->setLastJobType(last_job_type);
}

bool MachineProcessingContext::comparePrioritiesOfTwoSteps(long step_id1, long step_id2) {
    return machine_buffer->comparePrioritiesOfTwoSteps(step_id1, step_id2);
}