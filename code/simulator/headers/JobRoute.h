//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_JOBROUTE_H
#define SCHEDULING_JOBROUTE_H

#include "vector"
#include "Individual.h"
#include "Job.h"
#include "set"

class JobRoute {
private:
    long job_id;
    Job* job;
    std::vector<long> machine_list;
    std::set<long> machine_set;
    long current_index;
public:
    JobRoute(Job* job, Individual* individual);
    [[nodiscard]] long getJobId() const;
    std::vector<long> getMachineList();
    void fillMachineList(GenotypeNode* node);
    long getNextMachine();
    [[nodiscard]] long getCurrentIndex() const;
    bool checkHasFinished();
};


#endif //SCHEDULING_JOBROUTE_H
