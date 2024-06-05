//
// Created by mihael on 6/2/24.
//

#include "EvolutionStrategy.h"

#include <iostream>

EvolutionStrategy::EvolutionStrategy(
    EvaluationFunction* evaluation_function,
    CreationOperator* creation_operator,
    PerturbationOperator* perturbation_operator,
    CombinationOperator* combination_operator,
    int population_size,
    int number_of_evaluations,
    double new_units_per_generation_percentage
) :
    OptimizationAlgorithm(evaluation_function),
    OptimizationAlgorithmWithCreationOperator(evaluation_function, creation_operator),
    OptimizationAlgorithmWithPerturbationOperator(evaluation_function, perturbation_operator),
    OptimizationAlgorithmWithCombinationOperator(evaluation_function, combination_operator)
{
    this->number_of_evaluations = number_of_evaluations;
    this->new_units_per_generation = std::ceil(population_size * new_units_per_generation_percentage);
    if (this->new_units_per_generation == 0) {
        this->new_units_per_generation = 1;
    }
    this->selection_random_unit_generator = new UniformIntDistributionGenerator(0, population_size - 1);
}

EvolutionStrategy::~EvolutionStrategy() {
    delete selection_random_unit_generator;
}

void EvolutionStrategy::optimize(Population* population) {
    population->initialize(creation_operator, evaluation_function);

    int evaluations = 0;

    int iter = 0;
    while (evaluations < number_of_evaluations) {
        std::vector<EvaluatedGenotype*> new_units;
        for (int i = 0; i < new_units_per_generation; i++) {
            int const parent1 = selection_random_unit_generator->generate();
            int parent2;
            do {
                parent2 = selection_random_unit_generator->generate();
            } while (parent1 == parent2);

            auto const new_unit_genotype = combination_operator->combine(population->getGenotype(parent1)->genotype, population->getGenotype(parent2)->genotype);
            perturbation_operator->perturbate(new_unit_genotype);

            auto const fitness = evaluation_function->evaluate(new_unit_genotype);
            auto evaluated_unit = new EvaluatedGenotype(new_unit_genotype, fitness);
            new_units.push_back(evaluated_unit);
            evaluations++;
            if (evaluations >= number_of_evaluations) {
                break;
            }
        }
        population->insertGenotypes(new_units);
        iter++;
        std::cout << "ES ITER " << iter << ", err = " << population->getGenotype(0)->fitness_score << std::endl;
    }
}

