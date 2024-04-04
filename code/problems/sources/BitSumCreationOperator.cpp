//
// Created by mihael on 2/18/24.
//

#include "BitSumCreationOperator.h"

#include "BitSumGenotype.h"
#include "BitSumGenotypeBlueprint.h"
#include "SchedulingError.h"
#include "vector"

BitSumCreationOperator::BitSumCreationOperator(GenotypeBlueprint* genotype_blueprint) : CreationOperator(genotype_blueprint) {
    this->uniform_int_distribution_generator = new UniformIntDistributionGenerator(0, 1);
    auto bit_sum_genotype_blueprint = dynamic_cast<BitSumGenotypeBlueprint*>(genotype_blueprint);
    if (bit_sum_genotype_blueprint == nullptr) {
        throw SchedulingError("BitSumCreationOperator can only work with BitSumGenotypeBlueprint.");
    }
}

Genotype* BitSumCreationOperator::create() {
    auto bit_sum_genotype_blueprint = dynamic_cast<BitSumGenotypeBlueprint*>(this->genotype_blueprint);
    std::vector<int> bits(bit_sum_genotype_blueprint->number_of_bits);
    for (int i = 0; i < bit_sum_genotype_blueprint->number_of_bits; i++) {
        bits[i] = uniform_int_distribution_generator->generate();
    }
    return new BitSumGenotype(bits);
}
