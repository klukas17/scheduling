//
// Created by mihael on 5/23/24.
//

#include "CartesianGeneticProgrammingGenotypeBlueprint.h"

#include "UniformRealDistributionGenerator.h"

CartesianGeneticProgrammingGenotypeBlueprint::CartesianGeneticProgrammingGenotypeBlueprint(int rows, int cols, CGPFunctionsIndex* functions_index, double constant_min, double constant_max) {
    this->rows = rows;
    this->cols = cols;
    this->functions_index = functions_index;
    this->constant_generator = new UniformRealDistributionGenerator(constant_min, constant_max);
}

double CartesianGeneticProgrammingGenotypeBlueprint::generateConstant() {
    return constant_generator->generate();
}
