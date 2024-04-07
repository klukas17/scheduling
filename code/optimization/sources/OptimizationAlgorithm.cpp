//
// Created by mihael on 2/16/24.
//

#include "OptimizationAlgorithm.h"

OptimizationAlgorithm::OptimizationAlgorithm(EvaluationFunction *evaluation_function) {
    this->evaluation_function = evaluation_function;
}

OptimizationAlgorithm::~OptimizationAlgorithm() = default;

EvaluationFunction* OptimizationAlgorithm::getEvaluationFunction() const {
    return evaluation_function;
}
