//
// Created by mihael on 2/11/24.
//

#include "SimulatorStatistics.h"

SimulatorStatistics::SimulatorStatistics() = default;

std::map<long, JobStatistics *> SimulatorStatistics::getStatistics() {
    return statistics;
}

JobStatistics *SimulatorStatistics::getJobStatistics(long const job_id) {
    return statistics[job_id];
}

void SimulatorStatistics::addJobStatistics(JobStatistics *job_statistics) {
    statistics[job_statistics->getId()] = job_statistics;
}
