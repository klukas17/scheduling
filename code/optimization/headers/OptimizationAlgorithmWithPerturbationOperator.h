//
// Created by mihael on 2/18/24.
//

#ifndef OPTIMIZATIONALGORITHMWITHPERTURBATIONOPERATOR_H
#define OPTIMIZATIONALGORITHMWITHPERTURBATIONOPERATOR_H
#include "OptimizationAlgorithm.h"
#include "PerturbationOperator.h"


class OptimizationAlgorithmWithPerturbationOperator : public virtual OptimizationAlgorithm {
private:
    PerturbationOperator* perturbation_operator;;
public:
    OptimizationAlgorithmWithPerturbationOperator(EvaluationFunction* evaluation_function, PerturbationOperator* perturbation_operator);
    PerturbationOperator* getPerturbationOperator();
    ~OptimizationAlgorithmWithPerturbationOperator() override = 0;
};



#endif //OPTIMIZATIONALGORITHMWITHPERTURBATIONOPERATOR_H
