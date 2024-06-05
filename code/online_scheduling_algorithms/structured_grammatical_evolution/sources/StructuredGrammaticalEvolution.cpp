//
// Created by mihael on 5/31/24.
//

#include "StructuredGrammaticalEvolution.h"

#include "SGEPhenotypeBuilder.h"

StructuredGrammaticalEvolution::StructuredGrammaticalEvolution(SGEProgram* program) {
    this->program = program;
}

StructuredGrammaticalEvolution::~StructuredGrammaticalEvolution() {
    delete program;
}

SGEProgram* StructuredGrammaticalEvolution::getProgram() {
    return program;
}

Genotype* StructuredGrammaticalEvolution::copy() {
    auto copy = new StructuredGrammaticalEvolution(program->copy());
    copy->setInputs(inputs);
    return copy;
}


double StructuredGrammaticalEvolution::calculateScore(std::map<std::string, double> params) {
    return program->executeProgram(params);
}


