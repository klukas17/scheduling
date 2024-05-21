//
// Created by mihael on 5/20/24.
//

#include "TotalWeightedCompletionTimeObjectiveFunction.h"

TotalWeightedCompletionTimeObjectiveFunction::TotalWeightedCompletionTimeObjectiveFunction() = default;

double TotalWeightedCompletionTimeObjectiveFunction::evaluate(SimulatorStatistics* statistics) {
    double result = 0;
    for (auto [_, job_statistics] : statistics->getStatistics()) {
        if (job_statistics->getJobStatus() == SUCCESSFULLY_TERMINATED) {
            result += job_statistics->getWeight() * (job_statistics->getExitTime() - job_statistics->getReleaseTime());
        }
    }
    return result;
}

