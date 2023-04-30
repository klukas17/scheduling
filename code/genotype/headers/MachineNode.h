//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINENODE_H
#define SCHEDULING_MACHINENODE_H

#include "GenotypeNode.h"
#include "vector"

class MachineNode : public GenotypeNode {
private:
    long id;
    std::vector<long> job_processing_order;
public:
    MachineNode(long id);
    long getId();
    void add_job(long job_id);
    std::vector<long> getJobProcessingOrder();
};


#endif //SCHEDULING_MACHINENODE_H
