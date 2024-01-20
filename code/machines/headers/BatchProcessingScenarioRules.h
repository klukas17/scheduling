//
// Created by mihael on 10/1/23.
//

/**
 * @file BatchProcessingScenarioRules.h
 * @brief Defines the BatchProcessingScenarioRules class for managing rules related to batch processing scenarios.
 */

#ifndef SCHEDULING_BATCHPROCESSINGSCENARIORULES_H
#define SCHEDULING_BATCHPROCESSINGSCENARIORULES_H

#include "map"
#include "BatchProcessingScenario.h"

/**
 * @class BatchProcessingScenarioRules
 * @brief Represents rules related to batch processing scenarios.
 *
 * The BatchProcessingScenarioRules class provides functionality for representing rules related to batch processing scenarios.
 * It includes methods to add batch processing scenarios and find scenarios based on job identifiers.
 */
class BatchProcessingScenarioRules {
private:
    std::map<long, BatchProcessingScenario*> scenarios; /**< Map of batch processing scenarios with job type IDs as keys. */

public:
    /**
     * @brief Constructs an empty BatchProcessingScenarioRules object.
     */
    BatchProcessingScenarioRules();

    /**
     * @brief Adds a batch processing scenario to the rules.
     * @param batch_processing_scenario Pointer to the BatchProcessingScenario object to add.
     */
    void addBatchProcessingScenario(BatchProcessingScenario* batch_processing_scenario);

    /**
     * @brief Finds a batch processing scenario based on the given job identifier.
     * @param job_id The identifier of the job for which to find the batch processing scenario.
     * @return Pointer to the BatchProcessingScenario object, or nullptr if not found.
     */
    BatchProcessingScenario* findBatchProcessingScenario(long job_id);
};

#endif //SCHEDULING_BATCHPROCESSINGSCENARIORULES_H
