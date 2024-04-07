//
// Created by mihael on 4/4/24.
//

#ifndef STEADYSTATEGENETICALGORITHM_H
#define STEADYSTATEGENETICALGORITHM_H
#include "OptimizationAlgorithm.h"
#include "OptimizationAlgorithmWithCombinationOperator.h"
#include "OptimizationAlgorithmWithCreationOperator.h"
#include "OptimizationAlgorithmWithPerturbationOperator.h"
#include "UniformIntDistributionGenerator.h"


class SteadyStateGeneticAlgorithm final : public OptimizationAlgorithmWithCreationOperator, public OptimizationAlgorithmWithPerturbationOperator, public OptimizationAlgorithmWithCombinationOperator {
    int population_size;
    int iterations_count;
    UniformIntDistributionGenerator* selection_random_unit_generator;
public:
    SteadyStateGeneticAlgorithm(EvaluationFunction* evaluation_function, CreationOperator* creation_operator, PerturbationOperator* perturbation_operator, CombinationOperator* combination_operator, int population_size, int iterations_count);
    Genotype* optimize() override;
};



#endif //STEADYSTATEGENETICALGORITHM_H
