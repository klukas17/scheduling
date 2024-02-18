//
// Created by mihael on 2/16/24.
//

#ifndef OPTIMIZATIONALGORITHM_H
#define OPTIMIZATIONALGORITHM_H

#include "EvaluationFunction.h"
#include "Genotype.h"


class OptimizationAlgorithm {
private:
    EvaluationFunction* evaluation_function;
public:
    OptimizationAlgorithm(EvaluationFunction* evaluation_function);
    EvaluationFunction* getEvaluationFunction();
    virtual Genotype* optimize() = 0;
    virtual ~OptimizationAlgorithm() = 0;
};


#endif //OPTIMIZATIONALGORITHM_H
