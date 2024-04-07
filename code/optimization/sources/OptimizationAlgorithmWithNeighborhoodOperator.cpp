//
// Created by mihael on 2/18/24.
//

#include "OptimizationAlgorithmWithNeighborhoodOperator.h"

OptimizationAlgorithmWithNeighborhoodOperator::OptimizationAlgorithmWithNeighborhoodOperator(EvaluationFunction *evaluation_function, NeighborhoodOperator *neighborhood_operator) : OptimizationAlgorithm(evaluation_function) {
    this->neighborhood_operator = neighborhood_operator;
}

OptimizationAlgorithmWithNeighborhoodOperator::~OptimizationAlgorithmWithNeighborhoodOperator() = default;

NeighborhoodOperator *OptimizationAlgorithmWithNeighborhoodOperator::getNeighborhoodOperator() const {
    return neighborhood_operator;
}
