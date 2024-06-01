//
// Created by mihael on 5/20/24.
//

#include <iostream>

#include "CartesianGeneticProgrammingCombinationOperator.h"
#include "CartesianGeneticProgrammingCreationOperator.h"
#include "CartesianGeneticProgrammingGenotypeBlueprint.h"
#include "CartesianGeneticProgrammingPerturbationOperator.h"
#include "CartesianGeneticProgrammingSerializationOperator.h"
#include "GeneExpressionProgrammingCombinationOperator.h"
#include "GeneExpressionProgrammingCreationOperator.h"
#include "GeneExpressionProgrammingGenotypeBlueprint.h"
#include "GeneExpressionProgrammingPerturbationOperator.h"
#include "GeneExpressionProgrammingSerializationOperator.h"
#include "GrammaticalEvolutionCombinationOperator.h"
#include "GrammaticalEvolutionCreationOperator.h"
#include "GrammaticalEvolutionGenotypeBlueprint.h"
#include "GrammaticalEvolutionPerturbationOperator.h"
#include "GrammaticalEvolutionSerializationOperator.h"
#include "LGPRegisterInitializationStrategyCircularLoading.h"
#include "LinearGeneticProgrammingCombinationOperator.h"
#include "LinearGeneticProgrammingCreationOperator.h"
#include "LinearGeneticProgrammingGenotypeBlueprint.h"
#include "LinearGeneticProgrammingPerturbationOperator.h"
#include "LinearGeneticProgrammingSerializationOperator.h"
#include "MultiExpressionProgrammingCombinationOperator.h"
#include "MultiExpressionProgrammingCreationOperator.h"
#include "MultiExpressionProgrammingGenotypeBlueprint.h"
#include "MultiExpressionProgrammingPerturbationOperator.h"
#include "MultiExpressionProgrammingSerializationOperator.h"
#include "NeuralNetworkCreationOperator.h"
#include "NeuralNetworkGenotypeBlueprint.h"
#include "NeuralNetworkCombinationOperator.h"
#include "NeuralNetworkPerturbationOperator.h"
#include "NormalDistribution.h"
#include "RegressionFunction.h"
#include "StackBasedGeneticProgrammingCombinationOperator.h"
#include "StackBasedGeneticProgrammingCreationOperator.h"
#include "StackBasedGeneticProgrammingGenotypeBlueprint.h"
#include "StackBasedGeneticProgrammingPerturbationOperator.h"
#include "StackBasedGeneticProgrammingSerializationOperator.h"
#include "SteadyStateGeneticAlgorithm.h"
#include "StructuredGrammaticalEvolutionCombinationOperator.h"
#include "StructuredGrammaticalEvolutionCreationOperator.h"
#include "StructuredGrammaticalEvolutionGenotypeBlueprint.h"
#include "StructuredGrammaticalEvolutionPerturbationOperator.h"
#include "StructuredGrammaticalEvolutionSerializationOperator.h"

#include "TreeBasedGeneticProgrammingCombinationOperator.h"
#include "TreeBasedGeneticProgrammingCreationOperator.h"
#include "TreeBasedGeneticProgrammingGenotypeBlueprint.h"
#include "TreeBasedGeneticProgrammingPerturbationOperator.h"
#include "TreeBasedGeneticProgrammingSerializationOperator.h"

void neural_network() {
    int population_size = 50;
    int iterations_count = 1000000;

    auto evaluation_function = new RegressionFunction(true, {"x", "y"}, "../functions/function_01/data.txt");

    auto blueprint = new NeuralNetworkGenotypeBlueprint(new NormalDistribution(0, 0.1),{20, 10, 1});
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
    double leaf_param_chance = 0.4;
    int max_height = 4;

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

void cartesian_genetic_programming() {

    int rows = 2;
    int cols = 2;
    double perturbation_rate = 0.1;

    auto blueprint = new CartesianGeneticProgrammingGenotypeBlueprint(
        rows,
        cols,
        new CGPFunctionsIndex(),
        -1,
        1
    );
    auto creation_operator = new CartesianGeneticProgrammingCreationOperator(blueprint);
    auto combination_operator = new CartesianGeneticProgrammingCombinationOperator(blueprint);
    auto perturbation_operator = new CartesianGeneticProgrammingPerturbationOperator(blueprint, perturbation_rate);
    auto serialization_operator = new CartesianGeneticProgrammingSerializationOperator(blueprint);

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

void linear_genetic_programming() {

    auto register_initialization_strategy = new LGPRegisterInitializationStrategyCircularLoading();

    int number_of_registers = 5;
    int number_of_instructions = 5;
    double initialization_chance_of_nop = 0.5;
    double perturbation_chance_of_nop = 0.2;
    double perturbation_rate = 0.2;

    auto blueprint = new LinearGeneticProgrammingGenotypeBlueprint(
        register_initialization_strategy,
        number_of_registers,
        number_of_instructions,
        initialization_chance_of_nop,
        -1,
        1
    );
    auto creation_operator = new LinearGeneticProgrammingCreationOperator(blueprint);
    auto combination_operator = new LinearGeneticProgrammingCombinationOperator(blueprint);
    auto perturbation_operator = new LinearGeneticProgrammingPerturbationOperator(blueprint, perturbation_rate, perturbation_chance_of_nop);
    auto serialization_operator = new LinearGeneticProgrammingSerializationOperator(blueprint);

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

void stack_based_genetic_programming() {

    int number_of_instructions = 100;
    double initialization_chance_of_nop = 0.1;
    double push_constant_share = 0.05;
    double push_param_share = 0.2;
    double perturbation_chance_of_nop = 0.1;
    double perturbation_rate = 0.05;

    auto blueprint = new StackBasedGeneticProgrammingGenotypeBlueprint(
        number_of_instructions,
        initialization_chance_of_nop,
        push_constant_share,
        push_param_share,
        -1,
        1
    );

    auto creation_operator = new StackBasedGeneticProgrammingCreationOperator(blueprint);
    auto combination_operator = new StackBasedGeneticProgrammingCombinationOperator(blueprint);
    auto perturbation_operator = new StackBasedGeneticProgrammingPerturbationOperator(blueprint, perturbation_rate, perturbation_chance_of_nop);
    auto serialization_operator = new StackBasedGeneticProgrammingSerializationOperator(blueprint);

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

void gene_expression_programming() {

    int head_size = 10;
    double tail_chance_of_param = 0.8;
    double perturbation_rate = 0.2;
    double chance_of_transposition = 0.1;
    int transposition_max_length = 5;

    auto blueprint = new GeneExpressionProgrammingGenotypeBlueprint(
        head_size,
        tail_chance_of_param,
        -1,
        1
    );

    auto creation_operator = new GeneExpressionProgrammingCreationOperator(blueprint);
    auto combination_operator = new GeneExpressionProgrammingCombinationOperator(blueprint);
    auto perturbation_operator = new GeneExpressionProgrammingPerturbationOperator(blueprint, perturbation_rate, chance_of_transposition, transposition_max_length);
    auto serialization_operator = new GeneExpressionProgrammingSerializationOperator(blueprint);

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

void multi_expression_programming() {
    int number_of_instructions = 6;
    double perturbation_rate = 0.2;

    auto blueprint = new MultiExpressionProgrammingGenotypeBlueprint(
        number_of_instructions,
        -1,
        1
    );

    auto creation_operator = new MultiExpressionProgrammingCreationOperator(blueprint);
    auto combination_operator = new MultiExpressionProgrammingCombinationOperator(blueprint);
    auto perturbation_operator = new MultiExpressionProgrammingPerturbationOperator(blueprint, perturbation_rate);
    auto serialization_operator = new MultiExpressionProgrammingSerializationOperator(blueprint);

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

void grammatical_evolution() {
    int codons = 30;
    int max_number_of_wrapping = 0;
    double perturbation_rate = 0.2;

    auto blueprint = new GrammaticalEvolutionGenotypeBlueprint(
        codons,
        256,
        max_number_of_wrapping,
        -1,
        1
    );

    auto creation_operator = new GrammaticalEvolutionCreationOperator(blueprint);
    auto combination_operator = new GrammaticalEvolutionCombinationOperator(blueprint);
    auto perturbation_operator = new GrammaticalEvolutionPerturbationOperator(blueprint, perturbation_rate);
    auto serialization_operator = new GrammaticalEvolutionSerializationOperator(blueprint);

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

void structured_grammatical_evolution() {

    int max_depth = 3;
    auto perturbation_rate = 0.2;

    auto blueprint = new StructuredGrammaticalEvolutionGenotypeBlueprint(
        max_depth,
        -1,
        1
    );

    auto creation_operator = new StructuredGrammaticalEvolutionCreationOperator(blueprint);
    auto combination_operator = new StructuredGrammaticalEvolutionCombinationOperator(blueprint);
    auto perturbation_operator = new StructuredGrammaticalEvolutionPerturbationOperator(blueprint, perturbation_rate);
    auto serialization_operator = new StructuredGrammaticalEvolutionSerializationOperator(blueprint);

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
    // tree_based_genetic_programming();
    // cartesian_genetic_programming();
    // linear_genetic_programming();
    // stack_based_genetic_programming();
    // gene_expression_programming();
    // multi_expression_programming();
    // grammatical_evolution();
    structured_grammatical_evolution();
}
