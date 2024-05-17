//
// Created by mihael on 5/6/24.
//

#ifndef ONLINESCHEDULINGALGORITHMCLUSTERCOMBINATIONOPERATORWITHCOARSEGRANULARITY_H
#define ONLINESCHEDULINGALGORITHMCLUSTERCOMBINATIONOPERATORWITHCOARSEGRANULARITY_H

#include "OnlineSchedulingAlgorithmClusterCombinationOperator.h"

class OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity final : public OnlineSchedulingAlgorithmClusterCombinationOperator {
public:
    explicit OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(CombinationOperator* algorithm_combination_operator);
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //ONLINESCHEDULINGALGORITHMCLUSTERCOMBINATIONOPERATORWITHCOARSEGRANULARITY_H
