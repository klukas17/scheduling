//
// Created by mihael on 10/1/23.
//

/**
 * @file BatchProcessingScenarioRules.cpp
 * @brief Implements the member functions of the BatchProcessingScenarioRules class.
 */

#include "BatchProcessingScenarioRules.h"

BatchProcessingScenarioRules::BatchProcessingScenarioRules() {}

void BatchProcessingScenarioRules::addBatchProcessingScenario(BatchProcessingScenario *batch_processing_scenario) {
    scenarios[batch_processing_scenario->getJobType()->getId()] = batch_processing_scenario;
}

BatchProcessingScenario *BatchProcessingScenarioRules::findBatchProcessingScenario(long job_id) {
    return scenarios[job_id];
}