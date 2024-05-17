//
// Created by mihael on 2/16/24.
//

#ifndef OPTIMIZATIONALGORITHM_H
#define OPTIMIZATIONALGORITHM_H

#include "EvaluationFunction.h"
#include "Population.h"

class OptimizationAlgorithm {
protected:
    EvaluationFunction* evaluation_function;
public:
    explicit OptimizationAlgorithm(EvaluationFunction* evaluation_function);
    [[nodiscard]] EvaluationFunction* getEvaluationFunction() const;
    virtual void optimize(Population* population) = 0;
    virtual ~OptimizationAlgorithm() = 0;
};


#endif //OPTIMIZATIONALGORITHM_H
