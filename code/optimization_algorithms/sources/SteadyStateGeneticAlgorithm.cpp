//
// Created by mihael on 4/4/24.
//

#include "SteadyStateGeneticAlgorithm.h"

#include "EvaluatedGenotype.h"

SteadyStateGeneticAlgorithm::SteadyStateGeneticAlgorithm(EvaluationFunction* evaluation_function, CreationOperator* creation_operator, PerturbationOperator* perturbation_operator, CombinationOperator* combination_operator, int const population_size, int const iterations_count) :
    OptimizationAlgorithm(evaluation_function),
    OptimizationAlgorithmWithCreationOperator(evaluation_function, creation_operator),
    OptimizationAlgorithmWithPerturbationOperator(evaluation_function, perturbation_operator),
    OptimizationAlgorithmWithCombinationOperator(evaluation_function, combination_operator)
{
    this->population_size = population_size;
    this->iterations_count = iterations_count;
    this->selection_random_unit_generator = new UniformIntDistributionGenerator(0, population_size - 1);
}

Genotype* SteadyStateGeneticAlgorithm::optimize() {
    std::vector<EvaluatedGenotype*> population;

    for (int i = 0; i < population_size; i++) {
        auto const new_unit_genotype = creation_operator->create();
        auto const fitness = evaluation_function->evaluate(new_unit_genotype);
        auto evaluated_unit = new EvaluatedGenotype(new_unit_genotype, fitness);
        population.push_back(evaluated_unit);
    }

    auto comparator = [](const EvaluatedGenotype* a, const EvaluatedGenotype* b) {
        return a->fitness_score < b->fitness_score;
    };

    std::sort(population.begin(), population.end(), comparator);

    for (int i = 0; i < iterations_count; i++) {
        int const parent1 = selection_random_unit_generator->generate();
        int parent2;
        do {
            parent2 = selection_random_unit_generator->generate();
        } while (parent1 == parent2);

        auto const new_unit_genotype = combination_operator->combine(population[parent1]->genotype, population[parent2]->genotype);
        perturbation_operator->perturbate(new_unit_genotype);

        if (auto const fitness = evaluation_function->evaluate(new_unit_genotype); fitness < population.back()->fitness_score) {
            population.pop_back();
            auto evaluated_unit = new EvaluatedGenotype(new_unit_genotype, fitness);
            auto it = std::lower_bound(population.begin(), population.end(), evaluated_unit, comparator);
            population.insert(it, evaluated_unit);
        }
    }

    return population[0]->genotype;
}
