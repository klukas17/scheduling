//
// Created by mihael on 10/1/23.
//

#ifndef SCHEDULING_BATCHPROCESSINGSCENARIORULES_H
#define SCHEDULING_BATCHPROCESSINGSCENARIORULES_H

#include "map"
#include "BatchProcessingScenario.h"

class BatchProcessingScenarioRules {
    std::map<long, BatchProcessingScenario*> scenarios;
public:
    BatchProcessingScenarioRules();
    void addBatchProcessingScenario(BatchProcessingScenario* batch_processing_scenario);
    BatchProcessingScenario* findBatchProcessingScenario(long job_id);
};

#endif //SCHEDULING_BATCHPROCESSINGSCENARIORULES_H
