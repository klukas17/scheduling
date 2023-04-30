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
    void simulate(Individual* individual, std::vector<Job*> jobs, std::string logs_path);
};


#endif //SCHEDULING_SIMULATOR_H
