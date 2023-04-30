//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_JOBROUTE_H
#define SCHEDULING_JOBROUTE_H

#include "vector"
#include "Individual.h"

class JobRoute {
private:
    long job_id;
    std::vector<long> machine_list;
    long current_index;
public:
    JobRoute(long job_id, Individual* individual);
    [[nodiscard]] long getJobId() const;
    std::vector<long> getMachineList();
    void fillMachineList(GenotypeNode* node);
    long getNextMachine();
    [[nodiscard]] long getCurrentIndex() const;
    bool checkHasFinished();
};


#endif //SCHEDULING_JOBROUTE_H
