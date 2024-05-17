//
// Created by mihael on 5/8/24.
//

#include "ConstantProgrammingCombinationOperator.h"

ConstantProgrammingCombinationOperator::ConstantProgrammingCombinationOperator() = default;

Genotype* ConstantProgrammingCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    return genotype1->copy();
}

