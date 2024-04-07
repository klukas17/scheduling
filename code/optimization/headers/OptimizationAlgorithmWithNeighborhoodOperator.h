//
// Created by mihael on 2/18/24.
//

#ifndef OPTIMIZATIONALGORITHMWITHNEIGHBORHOODOPERATOR_H
#define OPTIMIZATIONALGORITHMWITHNEIGHBORHOODOPERATOR_H

#include "NeighborhoodOperator.h"
#include "OptimizationAlgorithm.h"


class OptimizationAlgorithmWithNeighborhoodOperator : public virtual OptimizationAlgorithm {
protected:
    NeighborhoodOperator* neighborhood_operator;
public:
    OptimizationAlgorithmWithNeighborhoodOperator(EvaluationFunction* evaluation_function, NeighborhoodOperator* neighborhood_operator);
    [[nodiscard]] NeighborhoodOperator* getNeighborhoodOperator() const;
    ~OptimizationAlgorithmWithNeighborhoodOperator() override = 0;
};



#endif //OPTIMIZATIONALGORITHMWITHNEIGHBORHOODOPERATOR_H
