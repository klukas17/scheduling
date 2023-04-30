//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINENODE_H
#define SCHEDULING_MACHINENODE_H

#include "GenotypeNode.h"
#include "vector"

class MachineNode : public GenotypeNode {
private:
    std::vector<long> job_processing_order;
public:
    explicit MachineNode(long id);
    std::vector<long> getJobProcessingOrder();
    void add_job(long job_id);
};


#endif //SCHEDULING_MACHINENODE_H
