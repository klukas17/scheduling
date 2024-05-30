//
// Created by mihael on 5/30/24.
//

#include "MultiExpressionProgramming.h"

MultiExpressionProgramming::MultiExpressionProgramming(MEPProgram* program) {
    this->program = program;
}

MultiExpressionProgramming::~MultiExpressionProgramming() {
    delete program;
}

MEPProgram* MultiExpressionProgramming::getProgram() {
    return program;
}

Genotype* MultiExpressionProgramming::copy() {
    auto copy = new MultiExpressionProgramming(program->copy());
    copy->setInputs(inputs);
    return copy;
}

double MultiExpressionProgramming::calculateScore(std::map<std::string, double> params) {
    return program->executeProgram(params);
}
