//
// Created by mihael on 2/18/24.
//

#include "BitSumEvaluationFunction.h"
#include "BitSumGenotype.h"
#include "SchedulingError.h"

BitSumEvaluationFunction::BitSumEvaluationFunction(bool minimization) : EvaluationFunction(minimization) {}

double BitSumEvaluationFunction::_evaluate(Genotype* genotype) {
    auto bit_sum_genotype = dynamic_cast<BitSumGenotype*>(genotype);
    if (bit_sum_genotype == nullptr) {
        throw SchedulingError("BitSumEvaluationFunction can only work with BitSumGenotype.");
    }
    double result = 0;
    for (const int bit : bit_sum_genotype->bits) {
        if (bit == 1) {
            result++;
        }
    }
    return result;
}
