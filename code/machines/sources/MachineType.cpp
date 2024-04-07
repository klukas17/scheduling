//
// Created by mihael on 29/04/23.
//

#include "MachineType.h"
#include <utility>

MachineType::MachineType(long const id, bool const preempt, std::vector<std::tuple<double, long, long>> setup_rules_raw_data, std::vector<std::tuple<long, long>> batch_processing_scenario_rules_raw_data) {
    this->id = id;
    this->preempt = preempt;
    this->setup_rules_raw_data = std::move(setup_rules_raw_data);
    this->setup_rules = new SetupRules();
    this->batch_processing_scenario_rules_raw_data = std::move(batch_processing_scenario_rules_raw_data);
    this->batch_processing_scenario_rules = new BatchProcessingScenarioRules();
}

long MachineType::getId() const {
    return id;
}

bool MachineType::getPreempt() const {
    return preempt;
}

SetupRules *MachineType::getSetupRules() const {
    return setup_rules;
}

BatchProcessingScenarioRules *MachineType::getBatchProcessingScenarioRules() const {
    return batch_processing_scenario_rules;
}


void MachineType::constructSetupAndBatchRules(JobTypeMap *job_type_map) {
    for (auto entry : setup_rules_raw_data) {
        double const time = std::get<0>(entry);
        JobType* from = job_type_map->getJobType(std::get<1>(entry));
        JobType* to = job_type_map->getJobType(std::get<2>(entry));
        setup_rules->addSetup(new Setup(from, to, time));
    }
    for (auto entry: batch_processing_scenario_rules_raw_data) {
        JobType* job_type = job_type_map->getJobType(std::get<0>(entry));
        long const jobs_per_batch = std::get<1>(entry);
        batch_processing_scenario_rules->addBatchProcessingScenario(new BatchProcessingScenario(job_type, jobs_per_batch));
    }
}