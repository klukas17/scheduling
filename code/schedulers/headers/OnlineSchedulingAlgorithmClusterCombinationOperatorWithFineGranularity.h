//
// Created by mihael on 5/5/24.
//

#ifndef ONLINESCHEDULINGALGORITHMCLUSTERCOMBINATIONOPERATORWITHFINEGRANULARITY_H
#define ONLINESCHEDULINGALGORITHMCLUSTERCOMBINATIONOPERATORWITHFINEGRANULARITY_H

#include "OnlineSchedulingAlgorithmClusterCombinationOperator.h"

class OnlineSchedulingAlgorithmClusterCombinationOperatorWithFineGranularity final : public OnlineSchedulingAlgorithmClusterCombinationOperator {
public:
    explicit OnlineSchedulingAlgorithmClusterCombinationOperatorWithFineGranularity(CombinationOperator* algorithm_combination_operator);
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //ONLINESCHEDULINGALGORITHMCLUSTERCOMBINATIONOPERATORWITHFINEGRANULARITY_H
