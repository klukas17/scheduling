//
// Created by mihael on 5/23/24.
//

#include "CartesianGeneticProgrammingCreationOperator.h"

#include <climits>

#include "CartesianGeneticProgramming.h"
#include "UniformIntDistributionGenerator.h"

CartesianGeneticProgrammingCreationOperator::CartesianGeneticProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<CartesianGeneticProgrammingGenotypeBlueprint*>(genotype_blueprint);
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

CartesianGeneticProgrammingCreationOperator::~CartesianGeneticProgrammingCreationOperator() {
    delete generator;
}

Genotype* CartesianGeneticProgrammingCreationOperator::create() {

    int output_index = generator->generate() % (blueprint->rows * blueprint->cols + blueprint->getInputs().size()) + 1;

    std::vector<CGPGridCell*> cells;
    std::map<long, double> constants;

    int inputs = blueprint->getInputs().size();
    int functions = blueprint->functions_index->getNumberOfFunctions() + 1; // +1 for constants
    int cell_index = inputs;

    for (int i = 0; i < blueprint->cols; i++) {
        for (int j = 0; j < blueprint->rows; j++) {
            cell_index++;
            int first_input_index = generator->generate() % inputs + 1;
            int second_input_index = generator->generate() % inputs + 1;
            int third_input_index = generator->generate() % inputs + 1;
            int function_index = generator->generate() % functions + 1;

            // constant
            if (function_index == functions) {
                constants[cell_index] = blueprint->generateConstant();
            }
            cells.push_back(new CGPGridCell(cell_index, first_input_index, second_input_index, third_input_index, function_index));
        }
        inputs += blueprint->rows;
    }

    auto grid = new CGPGrid(
        blueprint->rows,
        blueprint->cols,
        output_index,
        blueprint->functions_index,
        cells,
        constants,
        blueprint->getInputs()
    );

    auto cgp = new CartesianGeneticProgramming(grid);
    cgp->setInputs(blueprint->getInputs());
    return cgp;
}
