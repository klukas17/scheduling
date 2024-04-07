//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINETYPE_H
#define SCHEDULING_MACHINETYPE_H

#include "SetupRules.h"
#include "JobTypeMap.h"
#include <vector>
#include <tuple>
#include "BatchProcessingScenarioRules.h"

class MachineType {
protected:
    long id;
    bool preempt;
    SetupRules* setup_rules;
    std::vector<std::tuple<double, long, long>> setup_rules_raw_data;
    BatchProcessingScenarioRules* batch_processing_scenario_rules;
    std::vector<std::tuple<long, long>> batch_processing_scenario_rules_raw_data;
public:
    MachineType(long id, bool preempt, std::vector<std::tuple<double, long, long>> setup_rules_raw_data, std::vector<std::tuple<long, long>> batch_processing_scenario_rules_raw_data);
    [[nodiscard]] long getId() const;
    [[nodiscard]] bool getPreempt() const;
    [[nodiscard]] SetupRules* getSetupRules() const;
    [[nodiscard]] BatchProcessingScenarioRules* getBatchProcessingScenarioRules() const;
    void constructSetupAndBatchRules(JobTypeMap* job_type_map);
};

#endif //SCHEDULING_MACHINETYPE_H
