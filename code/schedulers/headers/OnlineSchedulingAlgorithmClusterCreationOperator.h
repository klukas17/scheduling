//
// Created by mihael on 5/5/24.
//

#ifndef ONLINESCHEDULINGALGORITHMCLUSTERCREATIONOPERATOR_H
#define ONLINESCHEDULINGALGORITHMCLUSTERCREATIONOPERATOR_H
#include "CreationOperator.h"
#include "OnlineSchedulingAlgorithmClusterGenotypeBlueprint.h"


class OnlineSchedulingAlgorithmClusterCreationOperator final : public CreationOperator {
    OnlineSchedulingAlgorithmClusterGenotypeBlueprint* blueprint;
    CreationOperator* algorithm_creation_operator;
public:
    OnlineSchedulingAlgorithmClusterCreationOperator(GenotypeBlueprint* genotype_blueprint, CreationOperator* algorithm_creation_operator);
    Genotype* create() override;
};



#endif //ONLINESCHEDULINGALGORITHMCLUSTERCREATIONOPERATOR_H
