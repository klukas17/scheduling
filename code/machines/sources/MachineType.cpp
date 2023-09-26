//
// Created by mihael on 29/04/23.
//

/**
 * @file MachineType.cpp
 * @brief Implements the member functions of the MachineType class.
 */

#include "MachineType.h"
#include <utility>

MachineType::MachineType(long id, bool preempt, std::vector<std::tuple<long, long, long>> setup_rules_raw_data) {
    this->id = id;
    this->preempt = preempt;
    this->setup_rules_raw_data = std::move(setup_rules_raw_data);
    this->setup_rules = new SetupRules();
}

long MachineType::getId() const {
    return id;
}

bool MachineType::getPreempt() const {
    return preempt;
}

SetupRules *MachineType::getSetupRules() {
    return setup_rules;
}

void MachineType::constructSetupRules(JobTypeMap *job_type_map) {
    for (auto entry : setup_rules_raw_data) {
        long time = std::get<0>(entry);
        JobType* from = job_type_map->getJobType(std::get<1>(entry));
        JobType* to = job_type_map->getJobType(std::get<2>(entry));
        setup_rules->addSetup(new Setup(from, to, time));
    }
}