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

void MachineProcessingContext::addJobToBuffer(long job_id) {
    machine_buffer->addJobToBuffer(job_id);
    jobs_in_buffer++;
}

bool MachineProcessingContext::getCurrentlyWorking() {
    return currently_working;
}

long MachineProcessingContext::takeJobFromBuffer() {
    return machine_buffer->takeJobFromBuffer();
}

MachineNode *MachineProcessingContext::getMachine() {
    return machine;
}

void MachineProcessingContext::decreaseJobsInBuffer() {
    currently_working = false;
    jobs_in_buffer--;
}

long MachineProcessingContext::getJobsInBuffer() {
    return jobs_in_buffer;
}

void MachineProcessingContext::setCurrentlyWorking() {
    currently_working = true;
}