//
// Created by mihael on 5/5/24.
//

#include "BitSumCombinationOperator.h"
#include "BitSumCreationOperator.h"
#include "BitSumEvaluationFunction.h"
#include "BitSumGenotype.h"
#include "BitSumGenotypeBlueprint.h"
#include "BitSumPerturbationOperator.h"
#include "iostream"
#include "SteadyStateGeneticAlgorithm.h"

int main() {
    constexpr int population_size = 200;
    constexpr int iterations_count = 10000;
    constexpr int number_of_bits = 100;
    constexpr double bit_flip_chance = 0.02;

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