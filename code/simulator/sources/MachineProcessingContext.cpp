//
// Created by mihael on 29/04/23.
//

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

void MachineProcessingContext::addStepToBuffer(long step_id, long job_id) {
    machine_buffer->addStepToBuffer(step_id, job_id);
    steps_in_buffer++;
}

std::pair<long, long> MachineProcessingContext::takeStepFromBuffer() {
    return machine_buffer->takeStepFromBuffer();
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