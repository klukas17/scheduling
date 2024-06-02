//
// Created by mihael on 6/2/24.
//

#ifndef EVOLUTIONSTRATEGY_H
#define EVOLUTIONSTRATEGY_H
#include "OptimizationAlgorithmWithCombinationOperator.h"
#include "OptimizationAlgorithmWithCreationOperator.h"
#include "OptimizationAlgorithmWithPerturbationOperator.h"
#include "UniformIntDistributionGenerator.h"


class EvolutionStrategy final :
    public OptimizationAlgorithmWithCreationOperator,
    public OptimizationAlgorithmWithPerturbationOperator,
    public OptimizationAlgorithmWithCombinationOperator
{
    int number_of_evaluations;
    int new_units_per_generation;
    UniformIntDistributionGenerator* selection_random_unit_generator;
public:
    EvolutionStrategy(
        EvaluationFunction* evaluation_function,
        CreationOperator* creation_operator,
        PerturbationOperator* perturbation_operator,
        CombinationOperator* combination_operator,
        int population_size,
        int number_of_evaluations,
        double new_units_per_generation_percentage
    );
    void optimize(Population* population) override;
};



#endif //EVOLUTIONSTRATEGY_H
