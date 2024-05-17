//
// Created by mihael on 5/3/24.
//

#include "RandomProgrammingCreationOperator.h"
#include "RandomProgramming.h"

RandomProgrammingCreationOperator::RandomProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<RandomProgrammingGenotypeBlueprint*>(genotype_blueprint);
}

Genotype* RandomProgrammingCreationOperator::create() {
    return new RandomProgramming(blueprint->lower, blueprint->upper);
}
