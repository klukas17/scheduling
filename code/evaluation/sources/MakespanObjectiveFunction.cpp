//
// Created by mihael on 2/11/24.
//

#include "MakespanObjectiveFunction.h"

MakespanObjectiveFunction::MakespanObjectiveFunction() = default;

double MakespanObjectiveFunction::evaluate(SimulatorStatistics *statistics) {
    double result = 0;
    for (auto [_, job_statistics] : statistics->getStatistics()) {
        if (job_statistics->getJobStatus() != UNTERMINATED && job_statistics->getExitTime() > result) {
            result = job_statistics->getExitTime();
        }
    }
    return result;
}
