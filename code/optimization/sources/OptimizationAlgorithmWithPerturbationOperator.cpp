//
// Created by mihael on 2/18/24.
//

#include "OptimizationAlgorithmWithPerturbationOperator.h"

OptimizationAlgorithmWithPerturbationOperator::OptimizationAlgorithmWithPerturbationOperator(EvaluationFunction *evaluation_function, PerturbationOperator *perturbation_operator) : OptimizationAlgorithm(evaluation_function) {
    this->perturbation_operator = perturbation_operator;
}

OptimizationAlgorithmWithPerturbationOperator::~OptimizationAlgorithmWithPerturbationOperator() = default;

PerturbationOperator *OptimizationAlgorithmWithPerturbationOperator::getPerturbationOperator() const {
    return perturbation_operator;
}
