//
// Created by mihael on 5/20/24.
//

#include <iostream>

#include "NeuralNetworkCreationOperator.h"
#include "NeuralNetworkGenotypeBlueprint.h"
#include "NeuralNetworkCombinationOperator.h"
#include "NeuralNetworkPerturbationOperator.h"
#include "NormalDistribution.h"
#include "RegressionFunction.h"
#include "SteadyStateGeneticAlgorithm.h"

#include "TreeBasedGeneticProgrammingCombinationOperator.h"
#include "TreeBasedGeneticProgrammingCreationOperator.h"
#include "TreeBasedGeneticProgrammingGenotypeBlueprint.h"
#include "TreeBasedGeneticProgrammingPerturbationOperator.h"
#include "TreeBasedGeneticProgrammingSerializationOperator.h"

void neural_network() {
    int population_size = 20;
    int iterations_count = 1000000;

    auto evaluation_function = new RegressionFunction(true, {"x", "y"}, "../functions/function_01/data.txt");

    auto blueprint = new NeuralNetworkGenotypeBlueprint(new NormalDistribution(0, 0.1),{20, 1});
    blueprint->setInputs({"x", "y"});
    auto creation_operator = new NeuralNetworkCreationOperator(blueprint);
    auto combination_operator = new NeuralNetworkCombinationOperator();
    auto perturbation_operator = new NeuralNetworkPerturbationOperator(new NormalDistribution(0, 0.1));

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
}

void tree_based_genetic_programming() {

    double leaf_const_chance = 0.1;
    double leaf_param_chance = 0.5;
    int max_height = 8;

    auto node_factory = new TBGPNodeFactory(leaf_const_chance, leaf_param_chance, -1, 1);
    auto blueprint = new TreeBasedGeneticProgrammingGenotypeBlueprint(node_factory, max_height);
    auto creation_operator = new TreeBasedGeneticProgrammingCreationOperator(blueprint);
    auto combination_operator = new TreeBasedGeneticProgrammingCombinationOperator(blueprint);
    auto perturbation_operator = new TreeBasedGeneticProgrammingPerturbationOperator(blueprint);
    auto serialization_operator = new TreeBasedGeneticProgrammingSerializationOperator(blueprint);

    auto evaluation_function = new RegressionFunction(true, {"x", "y"}, "../functions/function_01/data.txt");
    blueprint->setInputs({"x", "y"});

    int population_size = 50;
    int iterations_count = 100000;

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

    for (auto line : serialization_operator->serialize(population->getGenotype(0)->genotype)) {
        std::cout << line << std::endl;
    }
}


int main() {
    // neural_network();
    tree_based_genetic_programming();
}
