//
// Created by mihael on 5/23/24.
//

#include "CartesianGeneticProgrammingCombinationOperator.h"

#include <climits>

#include "CartesianGeneticProgramming.h"
#include "UniformIntDistributionGenerator.h"

CartesianGeneticProgrammingCombinationOperator::CartesianGeneticProgrammingCombinationOperator(CartesianGeneticProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

CartesianGeneticProgrammingCombinationOperator::~CartesianGeneticProgrammingCombinationOperator() {
    delete generator;
}

Genotype* CartesianGeneticProgrammingCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    auto cgp1 = dynamic_cast<CartesianGeneticProgramming*>(genotype1);
    auto cgp2 = dynamic_cast<CartesianGeneticProgramming*>(genotype2);

    auto grid1 = cgp1->getGrid();
    auto grid2 = cgp2->getGrid();

    auto cells1 = grid1->cells;
    auto cells2 = grid2->cells;

    auto constants1 = grid1->constants;
    auto constants2 = grid2->constants;

    auto cell_count = grid1->rows * grid1->cols;
    auto constant_index = grid1->getNumberOfFunctions() + 1;

    std::vector<CGPGridCell*> cells(cell_count);
    std::map<long, double> constants;
    auto inputs = cgp1->getInputs();
    auto output_index = grid2->output_index;

    auto break_point = generator->generate() % cell_count;

    for (int i = 0; i <= break_point; i++) {
        cells[i] = cells1[i]->copy();
        if (cells1[i]->cell_index == constant_index) {
            constants[cells1[i]->cell_index] = constants1[cells1[i]->cell_index];
        }
    }

    for (int i = break_point + 1; i < cell_count; i++) {
        cells[i] = cells2[i]->copy();
        if (cells2[i]->cell_index == constant_index) {
            constants[cells2[i]->cell_index] = constants2[cells2[i]->cell_index];
        }
    }

    auto grid = new CGPGrid(
        blueprint->rows,
        blueprint->cols,
        output_index,
        blueprint->functions_index,
        cells,
        constants,
        inputs
    );

    auto cgp = new CartesianGeneticProgramming(grid);
    cgp->setInputs(inputs);
    return cgp;
}

