//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_SIMULATOR_H
#define SCHEDULING_SIMULATOR_H

#include "string"
#include "Individual.h"
#include "Job.h"
#include "SimulatorStatistics.h"

class Simulator {
public:
    static SimulatorStatistics* simulate(Individual* individual, Topology* topology, const std::map<long, Job*>& jobs, bool enable_logging = false, const std::string& logs_path = "");
};

#endif //SCHEDULING_SIMULATOR_H
