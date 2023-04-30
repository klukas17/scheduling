//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_SERIALGROUPNODE_H
#define SCHEDULING_SERIALGROUPNODE_H

#include "GenotypeNode.h"
#include "vector"

class SerialGroupNode : public GenotypeNode {
private:
    std::vector<long> job_processing_order;
    std::vector<GenotypeNode*> body;
public:
    explicit SerialGroupNode(long id);
    std::vector<long> getJobProcessingOrder();
    void add_job(long job_id);
    std::vector<GenotypeNode*> getBody();
    void addNodeToBody(GenotypeNode* node);
};


#endif //SCHEDULING_SERIALGROUPNODE_H
