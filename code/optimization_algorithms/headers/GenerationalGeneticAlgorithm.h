//
// Created by mihael on 6/2/24.
//

#ifndef GENERATIONALGENETICALGORITHM_H
#define GENERATIONALGENETICALGORITHM_H
#include "OptimizationAlgorithmWithCombinationOperator.h"
#include "OptimizationAlgorithmWithCreationOperator.h"
#include "OptimizationAlgorithmWithPerturbationOperator.h"


class GenerationalGeneticAlgorithm final :
    public OptimizationAlgorithmWithCreationOperator,
    public OptimizationAlgorithmWithPerturbationOperator,
    public OptimizationAlgorithmWithCombinationOperator
{
    int population_size;
    int number_of_evaluations;
    double worst_unit_coef;
public:
    GenerationalGeneticAlgorithm(
        EvaluationFunction* evaluation_function,
        CreationOperator* creation_operator,
        PerturbationOperator* perturbation_operator,
        CombinationOperator* combination_operator,
        int population_size,
        int number_of_evaluations,
        double worst_unit_coef
    );
    ~GenerationalGeneticAlgorithm();
    void optimize(Population* population) override;
};



#endif //GENERATIONALGENETICALGORITHM_H
