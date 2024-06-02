//
// Created by mihael on 6/2/24.
//

#include "GenerationalGeneticAlgorithm.h"

#include <iostream>

#include "UniformRealDistributionGenerator.h"

GenerationalGeneticAlgorithm::GenerationalGeneticAlgorithm(
    EvaluationFunction* evaluation_function,
    CreationOperator* creation_operator,
    PerturbationOperator* perturbation_operator,
    CombinationOperator* combination_operator,
    int population_size,
    int generations_count,
    double worst_unit_coef
) :
    OptimizationAlgorithm(evaluation_function),
    OptimizationAlgorithmWithCreationOperator(evaluation_function, creation_operator),
    OptimizationAlgorithmWithPerturbationOperator(evaluation_function, perturbation_operator),
    OptimizationAlgorithmWithCombinationOperator(evaluation_function, combination_operator)
{
    this->population_size = population_size;
    this->generations_count = generations_count;
    this->worst_unit_coef = worst_unit_coef;
}

void GenerationalGeneticAlgorithm::optimize(Population* population) {
    population->initialize(creation_operator, evaluation_function);

    for (int gen = 0; gen < generations_count; gen++) {

        auto best_fitness = -population->getGenotype(0)->fitness_score;
        auto worst_fitness = -population->getGenotype(population_size - 1)->fitness_score;
        auto diff = best_fitness - worst_fitness;

        auto upper_limit = best_fitness;
        auto lower_limit = best_fitness - diff / (1 - worst_unit_coef);
        auto scale = upper_limit - lower_limit;

        double acc;
        std::vector<double> roulette;
        roulette.reserve(population_size);

        for (int i = 0; i < population_size; i++) {
            auto fitness = -population->getGenotype(i)->fitness_score;
            auto score = (fitness - lower_limit) / scale;
            acc += score;
            roulette.push_back(acc);
        }

        auto generator = new UniformRealDistributionGenerator(0, acc);

        std::vector<EvaluatedGenotype*> new_population;

        // elitism
        new_population.push_back(population->getGenotype(0)->copy());

        while (new_population.size() < population_size) {
            std::vector<Genotype*> parents;

            for (int i = 0; i < 2; i++) {
                double parent_score = generator->generate();

                int l = 0, r = population_size - 1, m = 0, solution_index = 0;;
                while (l <= r) {
                    m = (l + r) / 2;
                    if (roulette[m] >= parent_score) {
                        solution_index = m;
                    }
                    if (roulette[m] > parent_score) {
                        r = m - 1;
                    } else {
                        l = m + 1;
                    }
                }
                parents.push_back(population->getGenotype(solution_index)->genotype);
            }

            auto new_unit_genotype = combination_operator->combine(parents[0], parents[1]);
            perturbation_operator->perturbate(new_unit_genotype);

            auto const fitness = evaluation_function->evaluate(new_unit_genotype);
            auto evaluated_unit = new EvaluatedGenotype(new_unit_genotype, fitness);
            new_population.push_back(evaluated_unit);
        }

        population->replacePopulation(new_population);

        delete generator;
        std::cout << "  ITER " << gen + 1 << ", err = " << population->getGenotype(0)->fitness_score << std::endl;
    }
}
