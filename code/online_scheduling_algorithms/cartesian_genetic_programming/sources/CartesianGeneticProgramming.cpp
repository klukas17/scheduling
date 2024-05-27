//
// Created by mihael on 5/23/24.
//

#include "CartesianGeneticProgramming.h"

CartesianGeneticProgramming::CartesianGeneticProgramming(CGPGrid* grid) {
    this->grid = grid;
}

CartesianGeneticProgramming::~CartesianGeneticProgramming() {
    delete grid;
}

CGPGrid* CartesianGeneticProgramming::getGrid() {
    return grid;
}

Genotype* CartesianGeneticProgramming::copy() {
    auto copy = new CartesianGeneticProgramming(grid->copy());
    copy->setInputs(inputs);
    return copy;
}

double CartesianGeneticProgramming::calculateScore(std::map<std::string, double> params) {
    return grid->calculateOutput(params);
}
