//
// Created by mihael on 5/5/24.
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
    int population_size = 200;
    int iterations_count = 10000;
    int number_of_bits = 100;
    double bit_flip_chance = 0.02;

    auto const evaluation_function = new BitSumEvaluationFunction(false);
    auto const blueprint = new BitSumGenotypeBlueprint(number_of_bits);
    auto const creation_operator = new BitSumCreationOperator(blueprint);
    auto const perturbation_operator = new BitSumPerturbationOperator(bit_flip_chance);
    auto const combination_operator = new BitSumCombinationOperator();
    auto const ssga = new SteadyStateGeneticAlgorithm(
        evaluation_function,
        creation_operator,
        perturbation_operator,
        combination_operator,
        population_size,
        iterations_count
    );
    auto const population = new Population(population_size);
    ssga->optimize(population);
    auto solution = population->getGenotype(0)->genotype;
    for (auto const bit : dynamic_cast<BitSumGenotype*>(solution)->bits) {
        std::cout << bit;
    }
    std::cout << std::endl;
}

void es() {
    int population_size = 200;
    int number_of_evaluations = 10000;
    double new_units_per_generation_percentage = 0.1;
    int number_of_bits = 100;
    double bit_flip_chance = 0.02;

    auto const evaluation_function = new BitSumEvaluationFunction(false);
    auto const blueprint = new BitSumGenotypeBlueprint(number_of_bits);
    auto const creation_operator = new BitSumCreationOperator(blueprint);
    auto const perturbation_operator = new BitSumPerturbationOperator(bit_flip_chance);
    auto const combination_operator = new BitSumCombinationOperator();
    auto const es = new EvolutionStrategy(
        evaluation_function,
        creation_operator,
        perturbation_operator,
        combination_operator,
        population_size,
        number_of_evaluations,
        new_units_per_generation_percentage
    );
    auto const population = new Population(population_size);
    es->optimize(population);
    auto solution = population->getGenotype(0)->genotype;
    for (auto const bit : dynamic_cast<BitSumGenotype*>(solution)->bits) {
        std::cout << bit;
    }
    std::cout << std::endl;
}

void gga() {

    int population_size = 200;
    int generations_count = 20000;
    double worst_unit_coef = 0.1;
    int number_of_bits = 100;
    double bit_flip_chance = 0.02;

    auto const evaluation_function = new BitSumEvaluationFunction(false);
    auto const blueprint = new BitSumGenotypeBlueprint(number_of_bits);
    auto const creation_operator = new BitSumCreationOperator(blueprint);
    auto const perturbation_operator = new BitSumPerturbationOperator(bit_flip_chance);
    auto const combination_operator = new BitSumCombinationOperator();
    auto const gga = new GenerationalGeneticAlgorithm(
        evaluation_function,
        creation_operator,
        perturbation_operator,
        combination_operator,
        population_size,
        generations_count,
        worst_unit_coef
    );
    auto const population = new Population(population_size);
    gga->optimize(population);
    auto solution = population->getGenotype(0)->genotype;
    for (auto const bit : dynamic_cast<BitSumGenotype*>(solution)->bits) {
        std::cout << bit;
    }
    std::cout << std::endl;
}

void sia() {

    int population_size = 200;
    int number_of_evaluations = 100000;
    int number_of_clones = 5;
    int number_of_bits = 100;
    double bit_flip_chance = 0.02;

    auto const evaluation_function = new BitSumEvaluationFunction(false);
    auto const blueprint = new BitSumGenotypeBlueprint(number_of_bits);
    auto const creation_operator = new BitSumCreationOperator(blueprint);
    auto const perturbation_operator = new BitSumPerturbationOperator(bit_flip_chance);
    auto const sia = new SimpleImmunologicalAlgorithm(
        evaluation_function,
        creation_operator,
        perturbation_operator,
        population_size,
        number_of_evaluations,
        number_of_clones
    );
    auto const population = new Population(population_size);
    sia->optimize(population);
    auto solution = population->getGenotype(0)->genotype;
    for (auto const bit : dynamic_cast<BitSumGenotype*>(solution)->bits) {
        std::cout << bit;
    }
    std::cout << std::endl;
}

void clonalg() {

    int population_size = 200;
    int number_of_evaluations = 1000000;
    double beta = 0.5;
    int number_of_bits = 1000;
    double bit_flip_chance = 0.005;
    double new_random_units_percentage = 0.1;
    int perturbations_per_worst_unit = 20;

    auto const evaluation_function = new BitSumEvaluationFunction(false);
    auto const blueprint = new BitSumGenotypeBlueprint(number_of_bits);
    auto const creation_operator = new BitSumCreationOperator(blueprint);
    auto const perturbation_operator = new BitSumPerturbationOperator(bit_flip_chance);
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
    auto const population = new Population(population_size);
    clonalg->optimize(population);
    auto solution = population->getGenotype(0)->genotype;
    for (auto const bit : dynamic_cast<BitSumGenotype*>(solution)->bits) {
        std::cout << bit;
    }
    std::cout << std::endl;
}

int main() {
    // ssga();
    // es();
    // gga();
    // sia();
    clonalg();
}