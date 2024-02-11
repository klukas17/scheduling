//
// Created by mihael on 2/11/24.
//

#include "MakespanObjectiveFunction.h"

MakespanObjectiveFunction::MakespanObjectiveFunction() {}

double MakespanObjectiveFunction::evaluate(SimulatorStatistics *statistics) {
    double result = 0;
    for (auto pair : statistics->getStatistics()) {
        auto job_statistics = pair.second;
        if (job_statistics->getJobStatus() != UNTERMINATED && job_statistics->getExitTime() > result) {
            result = job_statistics->getExitTime();
        }
    }
    return result;
}
