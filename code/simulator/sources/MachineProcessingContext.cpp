//
// Created by mihael on 29/04/23.
//

#include "MachineProcessingContext.h"

MachineProcessingContext::MachineProcessingContext(MachineNode *machine) {
    this->machine = machine;
    this->machine_buffer = new MachineBuffer(machine->getJobProcessingOrder());
    this->jobs_in_buffer = 0;
    this->currently_working = false;
}

MachineNode *MachineProcessingContext::getMachine() {
    return machine;
}

void MachineProcessingContext::addJobToBuffer(long job_id) {
    machine_buffer->addJobToBuffer(job_id);
    jobs_in_buffer++;
}

long MachineProcessingContext::takeJobFromBuffer() {
    return machine_buffer->takeJobFromBuffer();
}

long MachineProcessingContext::getJobsInBuffer() const {
    return jobs_in_buffer;
}

void MachineProcessingContext::decreaseJobsInBuffer() {
    jobs_in_buffer--;
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