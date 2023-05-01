//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_JOBROUTE_H
#define SCHEDULING_JOBROUTE_H

#include "vector"
#include "Individual.h"
#include "Job.h"

class JobRoute {
private:
    Job* job;
    std::vector<long> machine_list;
    long current_index;
public:
    explicit JobRoute(Job *job);
    std::vector<long> getMachineList();
    void addMachineToMachineList(long machine_id);
    long getNextMachine();
    [[nodiscard]] long getCurrentIndex() const;
    bool checkHasFinished();
};


#endif //SCHEDULING_JOBROUTE_H
