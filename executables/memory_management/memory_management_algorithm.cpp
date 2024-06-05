//
// Created by mihael on 6/3/24.
//

#include "BitSumCombinationOperator.h"
#include "BitSumCreationOperator.h"
#include "BitSumEvaluationFunction.h"
#include "BitSumGenotype.h"
#include "BitSumGenotypeBlueprint.h"
#include "BitSumPerturbationOperator.h"
#include "ClonalSelectionAlgorithm.h"
#include "EvolutionStrategy.h"
#include "GenerationalGeneticAlgorithm.h"
#include "iostream"
#include "SimpleImmunologicalAlgorithm.h"
#include "SteadyStateGeneticAlgorithm.h"

void ssga() {
    int population_size = 20;
    int iterations_count = 100;
    int number_of_bits = 100;
    double bit_flip_chance = 0.02;

    auto const evaluation_function = new BitSumEvaluationFunction(false);
    auto const blueprint = new BitSumGenotypeBlueprint(number_of_bits);
    auto const creation_operator = new BitSumCreationOperator(blueprint);
    auto const perturbation_operator = new BitSumPerturbationOperator(bit_flip_chance);
    auto const combination_operator = new BitSumCombinationOperator();

    for (int i = 0; i < 100000000; i++) {

        auto const population = new Population(population_size);
        auto const ssga = new SteadyStateGeneticAlgorithm(
            evaluation_function,
            creation_operator,
            perturbation_operator,
            combination_operator,
            population_size,
            iterations_count
        );

        ssga->optimize(population);

        delete ssga;
        delete population;
    }
}

void gga() {
    int population_size = 20;
    int generations_count = 200;
    double worst_unit_coef = 0.1;
    int number_of_bits = 100;
    double bit_flip_chance = 0.02;

    auto const evaluation_function = new BitSumEvaluationFunction(false);
    auto const blueprint = new BitSumGenotypeBlueprint(number_of_bits);
    auto const creation_operator = new BitSumCreationOperator(blueprint);
    auto const perturbation_operator = new BitSumPerturbationOperator(bit_flip_chance);
    auto const combination_operator = new BitSumCombinationOperator();

    for (int i = 0; i < 100000000; i++) {

        auto const population = new Population(population_size);
        auto const gga = new GenerationalGeneticAlgorithm(
            evaluation_function,
            creation_operator,
            perturbation_operator,
            combination_operator,
            population_size,
            generations_count,
            worst_unit_coef
        );

        gga->optimize(population);

        delete gga;
        delete population;
    }
}

void es() {
    int population_size = 20;
    int number_of_evaluations = 100;
    double new_units_per_generation_percentage = 0.1;
    int number_of_bits = 100;
    double bit_flip_chance = 0.02;

    auto const evaluation_function = new BitSumEvaluationFunction(false);
    auto const blueprint = new BitSumGenotypeBlueprint(number_of_bits);
    auto const creation_operator = new BitSumCreationOperator(blueprint);
    auto const perturbation_operator = new BitSumPerturbationOperator(bit_flip_chance);
    auto const combination_operator = new BitSumCombinationOperator();

    for (int i = 0; i < 100000000; i++) {

        auto const population = new Population(population_size);
        auto const es = new EvolutionStrategy(
            evaluation_function,
            creation_operator,
            perturbation_operator,
            combination_operator,
            population_size,
            number_of_evaluations,
            new_units_per_generation_percentage
        );

        es->optimize(population);

        delete es;
        delete population;
    }
}

void sia() {

    int population_size = 20;
    int number_of_evaluations = 100;
    int number_of_clones = 5;
    int number_of_bits = 100;
    double bit_flip_chance = 0.02;

    auto const evaluation_function = new BitSumEvaluationFunction(false);
    auto const blueprint = new BitSumGenotypeBlueprint(number_of_bits);
    auto const creation_operator = new BitSumCreationOperator(blueprint);
    auto const perturbation_operator = new BitSumPerturbationOperator(bit_flip_chance);

    for (int i = 0; i < 100000000; i++) {

        auto const population = new Population(population_size);
        auto const sia = new SimpleImmunologicalAlgorithm(
            evaluation_function,
            creation_operator,
            perturbation_operator,
            population_size,
            number_of_evaluations,
            number_of_clones
        );

        sia->optimize(population);

        delete sia;
        delete population;
    }
}

void clonalg() {

    int population_size = 20;
    int number_of_evaluations = 1000;
    double beta = 0.5;
    int number_of_bits = 1000;
    double bit_flip_chance = 0.005;
    double new_random_units_percentage = 0.1;
    int perturbations_per_worst_unit = 20;

    auto const evaluation_function = new BitSumEvaluationFunction(false);
    auto const blueprint = new BitSumGenotypeBlueprint(number_of_bits);
    auto const creation_operator = new BitSumCreationOperator(blueprint);
    auto const perturbation_operator = new BitSumPerturbationOperator(bit_flip_chance);

    for (int i = 0; i < 100000000; i++) {

        auto const population = new Population(population_size);
        auto const clonalg = new ClonalSelectionAlgorithm(
            evaluation_function,
            creation_operator,
            perturbation_operator,
            population_size,
            number_of_evaluations,
            beta,
            new_random_units_percentage,
            perturbations_per_worst_unit
        );

        clonalg->optimize(population);

        delete clonalg;
        delete population;
    }
}

int main() {
    // ssga();
    // gga();
    // es();
    // sia();
    clonalg();
}