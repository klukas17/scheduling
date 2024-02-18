//
// Created by mihael on 2/18/24.
//

#ifndef OPTIMIZATIONALGORITHMWITHCOMBINATIONOPERATOR_H
#define OPTIMIZATIONALGORITHMWITHCOMBINATIONOPERATOR_H
#include "CombinationOperator.h"
#include "OptimizationAlgorithm.h"


class OptimizationAlgorithmWithCombinationOperator : public virtual OptimizationAlgorithm {
private:
    CombinationOperator* combination_operator;
public:
    OptimizationAlgorithmWithCombinationOperator(EvaluationFunction* evaluation_function, CombinationOperator* combination_operator);
    CombinationOperator* getCombinationOperator();
    ~OptimizationAlgorithmWithCombinationOperator() override = 0;
};



#endif //OPTIMIZATIONALGORITHMWITHCOMBINATIONOPERATOR_H
