//
// Created by mihael on 2/16/24.
//

#include "EvaluationFunction.h"

EvaluationFunction::EvaluationFunction(bool minimization) {
    this->evaluation_factor = minimization ? 1 : -1;
}

EvaluationFunction::~EvaluationFunction() = default;

double EvaluationFunction::evaluate(Genotype *genotype) {
    return evaluation_factor * _evaluate(genotype);
}
