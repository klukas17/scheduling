//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_GENOTYPENODE_H
#define SCHEDULING_GENOTYPENODE_H

#include "NodeType.h"
#include "vector"
#include "set"

class GenotypeNode {
protected:
    long id;
    NodeType node_type;
    std::vector<long> job_processing_order;
    std::set<long> job_set;
public:
    explicit GenotypeNode(long id);
    virtual ~GenotypeNode() = 0;
    [[nodiscard]] long getId() const;
    NodeType getNodeType();
    std::vector<long> getJobProcessingOrder();
    void addJob(long job_id);
    std::set<long> getJobSet();
};


#endif //SCHEDULING_GENOTYPENODE_H
