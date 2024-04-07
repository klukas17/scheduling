//
// Created by mihael on 2/18/24.
//

#include "OptimizationAlgorithmWithCreationOperator.h"

OptimizationAlgorithmWithCreationOperator::OptimizationAlgorithmWithCreationOperator(EvaluationFunction *evaluation_function, CreationOperator *creation_operator) : OptimizationAlgorithm(evaluation_function) {
    this->creation_operator = creation_operator;
}

OptimizationAlgorithmWithCreationOperator::~OptimizationAlgorithmWithCreationOperator() = default;

CreationOperator *OptimizationAlgorithmWithCreationOperator::getCreationOperator() const {
    return creation_operator;
}
