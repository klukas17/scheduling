//
// Created by mihael on 6/2/24.
//

#ifndef SIMPLEIMMUNOLOGICALALGORITHM_H
#define SIMPLEIMMUNOLOGICALALGORITHM_H

#include "OptimizationAlgorithmWithCreationOperator.h"
#include "OptimizationAlgorithmWithPerturbationOperator.h"


class SimpleImmunologicalAlgorithm final :
    public OptimizationAlgorithmWithCreationOperator,
    public OptimizationAlgorithmWithPerturbationOperator
{
    int number_of_evaluations;
    int number_of_clones;
    int population_size;
public:
    SimpleImmunologicalAlgorithm(
        EvaluationFunction* evaluation_function,
        CreationOperator* creation_operator,
        PerturbationOperator* perturbation_operator,
        int population_size,
        int number_of_evaluations,
        int number_of_clones
    );
    ~SimpleImmunologicalAlgorithm();
    void optimize(Population* population) override;
};



#endif //SIMPLEIMMUNOLOGICALALGORITHM_H
