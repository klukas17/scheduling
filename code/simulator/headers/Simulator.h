//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_SIMULATOR_H
#define SCHEDULING_SIMULATOR_H

#include "string"
#include "vector"
#include "Individual.h"
#include "Job.h"

class Simulator {
public:
    Simulator();
    static void simulate(Individual* individual, const std::vector<Job*>& jobs, bool enable_logging = false, const std::string& logs_path = "");
};


#endif //SCHEDULING_SIMULATOR_H
