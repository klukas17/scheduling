//
// Created by mihael on 4/4/24.
//

#include "SteadyStateGeneticAlgorithm.h"

#include <iostream>

#include "EvaluatedGenotype.h"

SteadyStateGeneticAlgorithm::SteadyStateGeneticAlgorithm(EvaluationFunction* evaluation_function, CreationOperator* creation_operator, PerturbationOperator* perturbation_operator, CombinationOperator* combination_operator, int const population_size, int const iterations_count) :
    OptimizationAlgorithm(evaluation_function),
    OptimizationAlgorithmWithCreationOperator(evaluation_function, creation_operator),
    OptimizationAlgorithmWithPerturbationOperator(evaluation_function, perturbation_operator),
    OptimizationAlgorithmWithCombinationOperator(evaluation_function, combination_operator)
{
    this->iterations_count = iterations_count;
    this->selection_random_unit_generator = new UniformIntDistributionGenerator(0, population_size - 1);
}

void SteadyStateGeneticAlgorithm::optimize(Population* population) {
    population->initialize(creation_operator, evaluation_function);

    for (int i = 0; i < iterations_count; i++) {
        int const parent1 = selection_random_unit_generator->generate();
        int parent2;
        do {
            parent2 = selection_random_unit_generator->generate();
        } while (parent1 == parent2);

        auto const new_unit_genotype = combination_operator->combine(population->getGenotype(parent1)->genotype, population->getGenotype(parent2)->genotype);
        perturbation_operator->perturbate(new_unit_genotype);

        auto const fitness = evaluation_function->evaluate(new_unit_genotype);
        auto evaluated_unit = new EvaluatedGenotype(new_unit_genotype, fitness);
        population->insertGenotype(evaluated_unit);
        std::cout << "  ITER " << i + 1 << ", err = " << population->getGenotype(0)->fitness_score << std::endl;
    }
}
