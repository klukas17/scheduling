//
// Created by mihael on 5/29/24.
//

#include "GeneExpressionProgramming.h"

GeneExpressionProgramming::GeneExpressionProgramming(GEPProgram* program) {
    this->program = program;
}

GeneExpressionProgramming::~GeneExpressionProgramming() {
    delete program;
}

GEPProgram* GeneExpressionProgramming::getProgram() {
    return program;
}

Genotype* GeneExpressionProgramming::copy() {
    auto copy = new GeneExpressionProgramming(program->copy());
    copy->setInputs(inputs);
    return copy;
}

double GeneExpressionProgramming::calculateScore(std::map<std::string, double> params) {
    return program->phenotype_root_node->eval(params);
}

