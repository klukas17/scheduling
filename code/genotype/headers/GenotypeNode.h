//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_GENOTYPENODE_H
#define SCHEDULING_GENOTYPENODE_H

#include "NodeType.h"
#include "vector"

class GenotypeNode {
protected:
    long id;
    NodeType node_type;
    GeneralNodeType general_node_type;
    std::vector<long> step_processing_order;
public:
    explicit GenotypeNode(long id);
    virtual ~GenotypeNode() = 0;
    [[nodiscard]] long getId() const;
    [[nodiscard]] NodeType getNodeType() const;
    [[nodiscard]] GeneralNodeType getGeneralNodeType() const;
    std::vector<long> getStepProcessingOrder();
    void addStep(long step_id);
};

#endif //SCHEDULING_GENOTYPENODE_H
