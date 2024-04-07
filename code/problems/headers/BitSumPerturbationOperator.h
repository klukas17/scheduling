//
// Created by mihael on 2/18/24.
//

#ifndef BITSUMPERTURBATIONOPERATOR_H
#define BITSUMPERTURBATIONOPERATOR_H

#include "PerturbationOperator.h"
#include "UniformRealDistributionGenerator.h"

class BitSumPerturbationOperator final : public PerturbationOperator {
    UniformRealDistributionGenerator* uniform_real_distribution_generator;
    double bit_flip_chance;
public:
    explicit BitSumPerturbationOperator(double bit_flip_chance);
    void perturbate(Genotype* genotype) override;
};



#endif //BITSUMPERTURBATIONOPERATOR_H
