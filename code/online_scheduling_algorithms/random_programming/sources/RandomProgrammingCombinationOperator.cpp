//
// Created by mihael on 5/3/24.
//

#include "RandomProgrammingCombinationOperator.h"

RandomProgrammingCombinationOperator::RandomProgrammingCombinationOperator() = default;

Genotype* RandomProgrammingCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    return genotype1->copy();
}

