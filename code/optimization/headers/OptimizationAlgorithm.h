//
// Created by mihael on 2/16/24.
//

#ifndef OPTIMIZATIONALGORITHM_H
#define OPTIMIZATIONALGORITHM_H
#include "CombinationOperator.h"
#include "CreationOperator.h"
#include "EvaluationFunction.h"
#include "Genotype.h"
#include "NeighborhoodOperator.h"
#include "PerturbationOperator.h"


class OptimizationAlgorithm {
public:
    virtual Genotype* optimize(
        CreationOperator* creation_operator,
        NeighborhoodOperator* neighborhood_operator,
        CombinationOperator* combination_operator,
        PerturbationOperator* perturbation_operator,
        EvaluationFunction* evaluation_function
        ) = 0;
    virtual ~OptimizationAlgorithm() = 0;
};



#endif //OPTIMIZATIONALGORITHM_H
