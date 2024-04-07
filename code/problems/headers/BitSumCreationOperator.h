//
// Created by mihael on 2/18/24.
//

#ifndef BITSUMCREATIONOPERATOR_H
#define BITSUMCREATIONOPERATOR_H

#include "CreationOperator.h"
#include "UniformIntDistributionGenerator.h"


class BitSumCreationOperator final : public CreationOperator {
    UniformIntDistributionGenerator* uniform_int_distribution_generator;
public:
    explicit BitSumCreationOperator(GenotypeBlueprint* genotype_blueprint);
    Genotype* create() override;
};



#endif //BITSUMCREATIONOPERATOR_H
