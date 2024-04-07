//
// Created by mihael on 29/04/23.
//

#include "JobType.h"

JobType::JobType(long const id, bool const preempt) {
    this->id = id;
    this->preempt = preempt;
}

long JobType::getId() const {
    return id;
}

double JobType::getProcessingTime(long const machine_type_id) {
    return processing_times[machine_type_id];
}

void JobType::setProcessingTime(long const machine_type_id, double const processing_time) {
    processing_times[machine_type_id] = processing_time;
}

std::set<long> JobType::getForbiddenMachineTypes() {
    return forbidden_machine_types;
}

void JobType::addForbiddenMachineType(long const machine_type_id) {
    forbidden_machine_types.insert(machine_type_id);
}

bool JobType::getPreempt() const {
    return preempt;
}