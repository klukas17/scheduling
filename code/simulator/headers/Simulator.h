//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_SIMULATOR_H
#define SCHEDULING_SIMULATOR_H

#include "string"
#include "Individual.h"
#include "Job.h"
#include "Scheduler.h"
#include "SimulatorState.h"
#include "SimulatorStatistics.h"

class Simulator {
    SimulatorState* simulator_state;
public:
    Simulator();
    SimulatorStatistics* simulate(Scheduler* scheduler, Topology* topology, const std::map<long, Job*>& jobs, bool enable_logging = false, const std::string& logs_path = "");
};

#endif //SCHEDULING_SIMULATOR_H
