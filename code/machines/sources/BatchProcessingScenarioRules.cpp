//
// Created by mihael on 10/1/23.
//

#include "BatchProcessingScenarioRules.h"

BatchProcessingScenarioRules::BatchProcessingScenarioRules() = default;

void BatchProcessingScenarioRules::addBatchProcessingScenario(BatchProcessingScenario *batch_processing_scenario) {
    scenarios[batch_processing_scenario->getJobType()->getId()] = batch_processing_scenario;
}

BatchProcessingScenario *BatchProcessingScenarioRules::findBatchProcessingScenario(long const job_id) {
    return scenarios[job_id];
}