//
// Created by mihael on 5/16/24.
//

#include "SimulatorStateJobInfo.h"

SimulatorStateJobInfo::SimulatorStateJobInfo() {
    this->machine_id = 0;
    this->remaining_time_on_machine = 0;
    this->currently_processing_on_machine = false;
    this->start_of_processing_time = 0;
}

long SimulatorStateJobInfo::getMachineId() {
    return machine_id;
}

void SimulatorStateJobInfo::setMachineId(long machine_id) {
    this->machine_id = machine_id;
}

double SimulatorStateJobInfo::getRemainingTimeOnMachine() {
    return remaining_time_on_machine;
}

void SimulatorStateJobInfo::setRemainingTimeOnMachine(double remaining_time_on_machine) {
    this->remaining_time_on_machine = remaining_time_on_machine;
}

bool SimulatorStateJobInfo::getCurrentlyProcessingOnMachine() {
    return currently_processing_on_machine;
}

void SimulatorStateJobInfo::setCurrentlyProcessingOnMachine(bool currently_processing_on_machine) {
    this->currently_processing_on_machine = currently_processing_on_machine;
}

double SimulatorStateJobInfo::getStartOfProcessingTime() {
    return start_of_processing_time;
}

void SimulatorStateJobInfo::setStartOfProcessingTime(double start_of_processing_time) {
    this->start_of_processing_time = start_of_processing_time;
}

double SimulatorStateJobInfo::calculateRemainingTime(double time) {
    if (!currently_processing_on_machine) {
        return remaining_time_on_machine;
    }
    return remaining_time_on_machine - (time - start_of_processing_time);
}
