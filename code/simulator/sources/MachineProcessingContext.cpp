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
    this->steps_in_buffer = 0;
    this->currently_working = false;
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