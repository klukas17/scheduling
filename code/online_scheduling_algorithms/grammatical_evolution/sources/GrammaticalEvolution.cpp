//
// Created by mihael on 5/30/24.
//

#include "GrammaticalEvolution.h"

GrammaticalEvolution::GrammaticalEvolution(GEProgram* program) {
    this->program = program;
}

GrammaticalEvolution::~GrammaticalEvolution() {
    delete program;
}

GEProgram* GrammaticalEvolution::getProgram() {
    return program;
}

Genotype* GrammaticalEvolution::copy() {
    auto copy = new GrammaticalEvolution(program->copy());
    copy->setInputs(inputs);
    return copy;
}

double GrammaticalEvolution::calculateScore(std::map<std::string, double> params) {
    return program->executeProgram(params);
}
