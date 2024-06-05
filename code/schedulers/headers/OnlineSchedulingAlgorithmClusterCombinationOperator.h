//
// Created by mihael on 5/6/24.
//

#ifndef ONLINESCHEDULINGALGORITHMCLUSTERCOMBINATIONOPERATOR_H
#define ONLINESCHEDULINGALGORITHMCLUSTERCOMBINATIONOPERATOR_H

#include <set>
#include "CombinationOperator.h"
#include "IntegerGenerator.h"

class OnlineSchedulingAlgorithmClusterCombinationOperator : public CombinationOperator {
protected:
    std::set<long> modifiable_machines;
    CombinationOperator* algorithm_combination_operator;
    IntegerGenerator* generator;
public:
    explicit OnlineSchedulingAlgorithmClusterCombinationOperator(CombinationOperator* algorithm_combination_operator);
    ~OnlineSchedulingAlgorithmClusterCombinationOperator();
    void setModifiableMachines(std::set<long> machines);
};



#endif //ONLINESCHEDULINGALGORITHMCLUSTERCOMBINATIONOPERATOR_H
