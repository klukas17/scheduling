//
// Created by mihael on 5/29/24.
//

#include "StackBasedGeneticProgramming.h"

StackBasedGeneticProgramming::StackBasedGeneticProgramming(SBGPProgram* program) {
    this->program = program;
}

StackBasedGeneticProgramming::~StackBasedGeneticProgramming() {
    delete program;
}

SBGPProgram* StackBasedGeneticProgramming::getProgram() {
    return program;
}

Genotype* StackBasedGeneticProgramming::copy() {
    auto copy = new StackBasedGeneticProgramming(program->copy());
    copy->setInputs(inputs);
    return copy;
}

double StackBasedGeneticProgramming::calculateScore(std::map<std::string, double> params) {
    return program->executeProgram(params);
}