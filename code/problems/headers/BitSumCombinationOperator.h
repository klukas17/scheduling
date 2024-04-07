//
// Created by mihael on 2/18/24.
//

#ifndef BITSUMCOMBINATIONOPERATOR_H
#define BITSUMCOMBINATIONOPERATOR_H

#include "CombinationOperator.h"
#include "UniformRealDistributionGenerator.h"

class BitSumCombinationOperator final : public CombinationOperator {
    UniformRealDistributionGenerator* uniform_real_distribution_generator;
public:
    BitSumCombinationOperator();
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //BITSUMCOMBINATIONOPERATOR_H
