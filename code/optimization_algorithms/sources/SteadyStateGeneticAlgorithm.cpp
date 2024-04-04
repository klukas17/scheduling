//
// Created by mihael on 4/4/24.
//

#include "SteadyStateGeneticAlgorithm.h"

#include "EvaluatedGenotype.h"

SteadyStateGeneticAlgorithm::SteadyStateGeneticAlgorithm(EvaluationFunction* evaluation_function, CreationOperator* creation_operator, PerturbationOperator* perturbation_operator, CombinationOperator* combination_operator, int population_size, int iterations_count) :
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
    EvaluatedGenotype* best_unit = nullptr;

    for (int i = 0; i < population_size; i++) {
        auto new_unit_genotype = creation_operator->create();
        auto fitness = evaluation_function->evaluate(new_unit_genotype);
        auto evaluated_unit = new EvaluatedGenotype(new_unit_genotype, fitness);
        population.push_back(evaluated_unit);
        if (best_unit == nullptr || best_unit->fitness_score > evaluated_unit->fitness_score) {
            best_unit = evaluated_unit;
        }
    }

    auto comparator = [](const EvaluatedGenotype* a, const EvaluatedGenotype* b) {
        return a->fitness_score < b->fitness_score;
    };

    std::sort(population.begin(), population.end(), comparator);

    for (int i = 0; i < iterations_count; i++) {
        int parent1, parent2;
        parent1 = selection_random_unit_generator->generate();
        do {
            parent2 = selection_random_unit_generator->generate();
        } while (parent1 == parent2);

        auto new_unit_genotype = combination_operator->combine(population[parent1]->genotype, population[parent2]->genotype);
        perturbation_operator->perturbate(new_unit_genotype);
        auto fitness = evaluation_function->evaluate(new_unit_genotype);

        if (fitness < population.back()->fitness_score) {
            population.pop_back();
            auto evaluated_unit = new EvaluatedGenotype(new_unit_genotype, fitness);
            auto it = std::lower_bound(population.begin(), population.end(), evaluated_unit, comparator);
            population.insert(it, evaluated_unit);
            if (best_unit == nullptr || best_unit->fitness_score > evaluated_unit->fitness_score) {
                best_unit = evaluated_unit;
            }
        }
    }

    return best_unit->genotype;
}
