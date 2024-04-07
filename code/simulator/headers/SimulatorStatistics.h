//
// Created by mihael on 2/11/24.
//

#ifndef SIMULATORSTATISTICS_H
#define SIMULATORSTATISTICS_H

#include <map>
#include "JobStatistics.h"

class SimulatorStatistics {
    std::map<long, JobStatistics*> statistics;
public:
    SimulatorStatistics();
    std::map<long, JobStatistics*> getStatistics();
    JobStatistics* getJobStatistics(long job_id);
    void addJobStatistics(JobStatistics* job_statistics);
};

#endif //SIMULATORSTATISTICS_H
