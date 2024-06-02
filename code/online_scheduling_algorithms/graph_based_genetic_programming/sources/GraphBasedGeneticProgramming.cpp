//
// Created by mihael on 6/1/24.
//

#include "GraphBasedGeneticProgramming.h"

GraphBasedGeneticProgramming::GraphBasedGeneticProgramming(GBGPProgram* program) {
    this->program = program;
}

GraphBasedGeneticProgramming::~GraphBasedGeneticProgramming() {
    delete program;
}

GBGPProgram* GraphBasedGeneticProgramming::getProgram() {
    return program;
}

Genotype* GraphBasedGeneticProgramming::copy() {
    auto copy = new GraphBasedGeneticProgramming(program->copy());
    copy->setInputs(inputs);
    return copy;
}

double GraphBasedGeneticProgramming::calculateScore(std::map<std::string, double> params) {
    return program->executeProgram(params);
}
