//
// Created by mihael on 2/18/24.
//

#include "BitSumCombinationOperator.h"

#include "BitSumGenotype.h"
#include "SchedulingError.h"

BitSumCombinationOperator::BitSumCombinationOperator() {
    this->uniform_real_distribution_generator = new UniformRealDistributionGenerator(0, 1);
}

Genotype* BitSumCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    auto bit_sum_genotype_1 = dynamic_cast<BitSumGenotype*>(genotype1);
    auto bit_sum_genotype_2 = dynamic_cast<BitSumGenotype*>(genotype2);
    if (bit_sum_genotype_1 == nullptr || bit_sum_genotype_2 == nullptr) {
        throw SchedulingError("BitSumCombinationOperator can only work with BitSumGenotype.");
    }
    std::vector<int> bits(bit_sum_genotype_1->bits.size());
    for (int i = 0; i < bits.size(); i++) {
        if (uniform_real_distribution_generator->generate() < 0.5) {
            bits[i] = bit_sum_genotype_1->bits[i];
        } else {
            bits[i] = bit_sum_genotype_2->bits[i];
        }
    }
    return new BitSumGenotype(bits);
}
