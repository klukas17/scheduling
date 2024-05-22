//
// Created by mihael on 5/22/24.
//

#include "DiscountedTotalWeightedCompletionTimeObjectiveFunction.h"
#include <cmath>

DiscountedTotalWeightedCompletionTimeObjectiveFunction::DiscountedTotalWeightedCompletionTimeObjectiveFunction() = default;

double DiscountedTotalWeightedCompletionTimeObjectiveFunction::evaluate(SimulatorStatistics* statistics) {
    double result = 0;
    for (auto [_, job_statistics] : statistics->getStatistics()) {
        result += job_statistics->getWeight() * (
            job_statistics->getJobStatus() == SUCCESSFULLY_TERMINATED ?
            1 - exp(-0.01 * (job_statistics->getExitTime() - job_statistics->getReleaseTime())) :
            5
        );
    }
    return result;
}

