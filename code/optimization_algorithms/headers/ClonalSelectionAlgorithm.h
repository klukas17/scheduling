//
// Created by mihael on 6/2/24.
//

#ifndef CLONALSELECTIONALGORITHM_H
#define CLONALSELECTIONALGORITHM_H
#include "OptimizationAlgorithmWithCreationOperator.h"
#include "OptimizationAlgorithmWithPerturbationOperator.h"


class ClonalSelectionAlgorithm final :
    public OptimizationAlgorithmWithCreationOperator,
    public OptimizationAlgorithmWithPerturbationOperator
{
    int number_of_evaluations;
    int population_size;
    double beta;
    double new_random_units_percentage;
public:
    ClonalSelectionAlgorithm(
        EvaluationFunction* evaluation_function,
        CreationOperator* creation_operator,
        PerturbationOperator* perturbation_operator,
        int population_size,
        int number_of_evaluations,
        double beta,
        double new_random_units_percentage
    );
    void optimize(Population* population) override;
};



#endif //CLONALSELECTIONALGORITHM_H
