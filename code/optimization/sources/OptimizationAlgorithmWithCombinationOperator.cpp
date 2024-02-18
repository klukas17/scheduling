//
// Created by mihael on 2/18/24.
//

#include "OptimizationAlgorithmWithCombinationOperator.h"

OptimizationAlgorithmWithCombinationOperator::OptimizationAlgorithmWithCombinationOperator(EvaluationFunction *evaluation_function, CombinationOperator *combination_operator) : OptimizationAlgorithm(evaluation_function) {
    this->combination_operator = combination_operator;
}

OptimizationAlgorithmWithCombinationOperator::~OptimizationAlgorithmWithCombinationOperator() = default;

CombinationOperator *OptimizationAlgorithmWithCombinationOperator::getCombinationOperator() {
    return combination_operator;
}
