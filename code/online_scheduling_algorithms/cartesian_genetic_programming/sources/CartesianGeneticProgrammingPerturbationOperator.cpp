//
// Created by mihael on 5/23/24.
//

#include "CartesianGeneticProgrammingPerturbationOperator.h"

#include <climits>

#include "CartesianGeneticProgramming.h"
#include "UniformIntDistributionGenerator.h"

CartesianGeneticProgrammingPerturbationOperator::CartesianGeneticProgrammingPerturbationOperator(CartesianGeneticProgrammingGenotypeBlueprint* blueprint, double perturbation_rate) {
    this->blueprint = blueprint;
    this->perturbation_rate = perturbation_rate;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

CartesianGeneticProgrammingPerturbationOperator::~CartesianGeneticProgrammingPerturbationOperator() {
    delete generator;
}

void CartesianGeneticProgrammingPerturbationOperator::perturbate(Genotype* genotype) {
    auto cgp = dynamic_cast<CartesianGeneticProgramming*>(genotype);
    auto grid = cgp->getGrid();
    auto constant_index = grid->getNumberOfFunctions() + 1;
    auto inputs_number = cgp->getInputs().size();

    auto cells = grid->rows * grid->cols + 1;
    auto changes = cells * perturbation_rate;

    for (int i = 0; i < changes; i++) {
        auto cell_index = generator->generate() % cells;
        // output cell
        if (cell_index == cells - 1) {
            grid->output_index = generator->generate() % (blueprint->rows * blueprint->cols + blueprint->getInputs().size()) + 1;
        } else {
            auto cell = grid->cells[cell_index];
            auto index_to_change = generator->generate() % 4;
            if (index_to_change == 0) {
                auto range = (cell->cell_index - inputs_number) / blueprint->rows * blueprint->rows + inputs_number;
                cell->first_input_index = generator->generate() % range + 1;
            } else if (index_to_change == 1) {
                auto range = (cell->cell_index - inputs_number) / blueprint->rows * blueprint->rows + inputs_number;
                cell->second_input_index = generator->generate() % range + 1;
            } else if (index_to_change == 2) {
                auto range = (cell->cell_index - inputs_number) / blueprint->rows * blueprint->rows + inputs_number;
                cell->third_input_index = generator->generate() % range + 1;
            } else if (index_to_change == 3) {
                if (cell->function_index == constant_index) {
                    grid->removeConstant(cell->cell_index);
                }
                cell->function_index = generator->generate() % (grid->functions_index->getNumberOfFunctions() + 1) + 1;
                if (cell->function_index == constant_index) {
                    auto constant = blueprint->generateConstant();
                    grid->addConstant(cell->cell_index, constant);
                }
            }
        }
    }
}

