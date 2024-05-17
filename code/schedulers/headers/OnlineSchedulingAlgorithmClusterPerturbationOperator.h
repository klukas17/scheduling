//
// Created by mihael on 5/5/24.
//

#ifndef ONLINESCHEDULINGALGORITHMCLUSTERPERTURBATIONOPERATOR_H
#define ONLINESCHEDULINGALGORITHMCLUSTERPERTURBATIONOPERATOR_H

#include <set>
#include "PerturbationOperator.h"


class OnlineSchedulingAlgorithmClusterPerturbationOperator final : public PerturbationOperator {
    std::set<long> modifiable_machines;
    PerturbationOperator* algorithm_perturbation_operator;
public:
    explicit OnlineSchedulingAlgorithmClusterPerturbationOperator(PerturbationOperator* algorithm_perturbation_operator);
    void setModifiableMachines(std::set<long> machines);
    void perturbate(Genotype* genotype) override;
};



#endif //ONLINESCHEDULINGALGORITHMCLUSTERPERTURBATIONOPERATOR_H
