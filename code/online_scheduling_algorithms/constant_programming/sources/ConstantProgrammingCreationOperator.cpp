//
// Created by mihael on 5/8/24.
//

#include "ConstantProgrammingCreationOperator.h"

#include "ConstantProgramming.h"

ConstantProgrammingCreationOperator::ConstantProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<ConstantProgrammingGenotypeBlueprint*>(genotype_blueprint);
}

Genotype* ConstantProgrammingCreationOperator::create() {
    return new ConstantProgramming(blueprint->constant);
}

