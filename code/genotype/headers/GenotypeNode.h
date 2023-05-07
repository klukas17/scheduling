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
    GeneralNodeType general_node_type;
    std::vector<long> step_processing_order;
    std::set<long> predecessor_node_ids;
public:
    explicit GenotypeNode(long id);
    virtual ~GenotypeNode() = 0;
    [[nodiscard]] long getId() const;
    NodeType getNodeType();
    GeneralNodeType getGeneralNodeType();
    std::vector<long> getStepProcessingOrder();
    void addStep(long step_id);
    std::set<long> getPredecessorIds();
    void addPredecessorId(long node_id);
};


#endif //SCHEDULING_GENOTYPENODE_H
