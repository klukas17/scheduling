//
// Created by mihael on 29/04/23.
//

/**
 * @file JobType.cpp
 * @brief Implements the member functions of the JobType class.
 */

#include "JobType.h"

JobType::JobType(long id, bool preempt) {
    this->id = id;
    this->preempt = preempt;
}

long JobType::getId() const {
    return id;
}

long JobType::getProcessingTime(long machine_type_id) {
    return processing_times[machine_type_id];
}

void JobType::setProcessingTime(long machine_id, long processing_time) {
    processing_times[machine_id] = processing_time;
}

std::set<long> JobType::getForbiddenMachineTypes() {
    return forbidden_machine_types;
}

void JobType::addForbiddenMachineType(long machine_type_id) {
    forbidden_machine_types.insert(machine_type_id);
}

bool JobType::getPreempt() const {
    return preempt;
}