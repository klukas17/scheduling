//
// Created by mihael on 2/18/24.
//

#ifndef OPTIMIZATIONALGORITHMWITHCREATIONOPERATOR_H
#define OPTIMIZATIONALGORITHMWITHCREATIONOPERATOR_H

#include "CreationOperator.h"
#include "OptimizationAlgorithm.h"


class OptimizationAlgorithmWithCreationOperator : public virtual OptimizationAlgorithm {
protected:
    CreationOperator* creation_operator;
public:
    OptimizationAlgorithmWithCreationOperator(EvaluationFunction* evaluation_function, CreationOperator* creation_operator);
    [[nodiscard]] CreationOperator* getCreationOperator() const;
    ~OptimizationAlgorithmWithCreationOperator() override = 0;
};



#endif //OPTIMIZATIONALGORITHMWITHCREATIONOPERATOR_H
