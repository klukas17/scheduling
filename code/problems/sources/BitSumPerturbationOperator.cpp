//
// Created by mihael on 2/18/24.
//

#include "BitSumPerturbationOperator.h"
#include "SchedulingError.h"
#include "BitSumGenotype.h"

BitSumPerturbationOperator::BitSumPerturbationOperator(double bit_flip_chance) {
    this->uniform_real_distribution_generator = new UniformRealDistributionGenerator(0, 1);
    this->bit_flip_chance = bit_flip_chance;
}

void BitSumPerturbationOperator::perturbate(Genotype* genotype) {
    auto bit_sum_genotype = dynamic_cast<BitSumGenotype*>(genotype);
    if (bit_sum_genotype == nullptr) {
        throw SchedulingError("BitSumPerturbationOperator can only work with BitSumGenotype.");
    }
    for (int i = 0; i < bit_sum_genotype->bits.size(); i++) {
        if (uniform_real_distribution_generator->generate() < bit_flip_chance) {
            bit_sum_genotype->bits[i] = 1 - bit_sum_genotype->bits[i];
        }
    }
}
