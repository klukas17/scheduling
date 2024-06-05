//
// Created by mihael on 6/3/24.
//

#include <iostream>

#include "CartesianGeneticProgrammingCombinationOperator.h"
#include "CartesianGeneticProgrammingCreationOperator.h"
#include "CartesianGeneticProgrammingGenotypeBlueprint.h"
#include "CartesianGeneticProgrammingPerturbationOperator.h"
#include "CartesianGeneticProgrammingSerializationOperator.h"
#include "ConstantProgrammingCombinationOperator.h"
#include "ConstantProgrammingCreationOperator.h"
#include "ConstantProgrammingGenotypeBlueprint.h"
#include "ConstantProgrammingPerturbationOperator.h"
#include "ConstantProgrammingSerializationOperator.h"
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
#include "GraphBasedGeneticProgrammingCombinationOperator.h"
#include "GraphBasedGeneticProgrammingCreationOperator.h"
#include "GraphBasedGeneticProgrammingGenotypeBlueprint.h"
#include "GraphBasedGeneticProgrammingPerturbationOperator.h"
#include "GraphBasedGeneticProgrammingSerializationOperator.h"
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
#include "NeuralNetworkCombinationOperator.h"
#include "NeuralNetworkCreationOperator.h"
#include "NeuralNetworkGenotypeBlueprint.h"
#include "NeuralNetworkPerturbationOperator.h"
#include "NeuralNetworkSerializationOperator.h"
#include "NormalDistribution.h"
#include "RandomProgrammingCombinationOperator.h"
#include "RandomProgrammingCreationOperator.h"
#include "RandomProgrammingGenotypeBlueprint.h"
#include "RandomProgrammingPerturbationOperator.h"
#include "RandomProgrammingSerializationOperator.h"
#include "StackBasedGeneticProgrammingCombinationOperator.h"
#include "StackBasedGeneticProgrammingCreationOperator.h"
#include "StackBasedGeneticProgrammingGenotypeBlueprint.h"
#include "StackBasedGeneticProgrammingPerturbationOperator.h"
#include "StackBasedGeneticProgrammingSerializationOperator.h"
#include "StructuredGrammaticalEvolutionCombinationOperator.h"
#include "StructuredGrammaticalEvolutionCreationOperator.h"
#include "StructuredGrammaticalEvolutionGenotypeBlueprint.h"
#include "StructuredGrammaticalEvolutionPerturbationOperator.h"
#include "StructuredGrammaticalEvolutionSerializationOperator.h"
#include "TBGPNodeFactory.h"
#include "TreeBasedGeneticProgrammingCombinationOperator.h"
#include "TreeBasedGeneticProgrammingCreationOperator.h"
#include "TreeBasedGeneticProgrammingGenotypeBlueprint.h"
#include "TreeBasedGeneticProgrammingPerturbationOperator.h"
#include "TreeBasedGeneticProgrammingSerializationOperator.h"

void loop(
    CreationOperator* creation_operator,
    CombinationOperator* combination_operator,
    PerturbationOperator* perturbation_operator,
    SerializationOperator* serialization_operator
) {
    for (int i = 0; i < 100000000; i++) {

        std::cout << i << std::endl;

        auto x = creation_operator->create();
        auto a = serialization_operator->serialize(x);
        auto y = serialization_operator->deserialize(a);
        auto b = serialization_operator->serialize(y);

        if (a.size() != b.size()) {
            throw;
        }
        for (int j = 0; j < a.size(); j++) {
            if (a[j] != b[j]) {
                throw;
            }
        }

        delete y;
        y = creation_operator->create();

        for (int j = 0; j < 1000; j++) {
            std::cout << i << "\t" << j << std::endl;
            auto y_ = y;
            y = combination_operator->combine(x, y);
            perturbation_operator->perturbate(y);
            delete y_;
        }

        delete x;
        delete y;
    }
}

void cp() {
    auto blueprint = new ConstantProgrammingGenotypeBlueprint(0);
    blueprint->setInputs({"x", "y", "z", "w"});
    auto creation_operator = new ConstantProgrammingCreationOperator(blueprint);
    auto combination_operator = new ConstantProgrammingCombinationOperator();
    auto perturbation_operator = new ConstantProgrammingPerturbationOperator();
    auto serialization_operator = new ConstantProgrammingSerializationOperator();

    loop(creation_operator, combination_operator, perturbation_operator, serialization_operator);
}

void rp() {
    auto blueprint = new RandomProgrammingGenotypeBlueprint(0, 1);
    blueprint->setInputs({"x", "y", "z", "w"});
    auto creation_operator = new RandomProgrammingCreationOperator(blueprint);
    auto combination_operator = new RandomProgrammingCombinationOperator();
    auto perturbation_operator = new RandomProgrammingPerturbationOperator();
    auto serialization_operator = new RandomProgrammingSerializationOperator();

    loop(creation_operator, combination_operator, perturbation_operator, serialization_operator);
}

void nn() {
    auto blueprint = new NeuralNetworkGenotypeBlueprint(new NormalDistribution(0, 1), {2, 4, 6}, "sigm");
    blueprint->setInputs({"x", "y", "z", "w"});
    auto creation_operator = new NeuralNetworkCreationOperator(blueprint);
    auto combination_operator = new NeuralNetworkCombinationOperator();
    auto perturbation_operator = new NeuralNetworkPerturbationOperator(new NormalDistribution(0, 1));
    auto serialization_operator = new NeuralNetworkSerializationOperator(blueprint);

    loop(creation_operator, combination_operator, perturbation_operator, serialization_operator);
}

void tbgp() {
    double leaf_const_chance = 0.1;
    double leaf_param_chance = 0.2;
    int max_height = 10;

    auto node_factory = new TBGPNodeFactory(leaf_const_chance, leaf_param_chance, -1, 1);
    node_factory->setInputs({"x", "y", "z", "w"});
    auto blueprint = new TreeBasedGeneticProgrammingGenotypeBlueprint(node_factory, max_height);
    blueprint->setInputs({"x", "y", "z", "w"});
    auto creation_operator = new TreeBasedGeneticProgrammingCreationOperator(blueprint);
    auto combination_operator = new TreeBasedGeneticProgrammingCombinationOperator(blueprint);
    auto perturbation_operator = new TreeBasedGeneticProgrammingPerturbationOperator(blueprint);
    auto serialization_operator = new TreeBasedGeneticProgrammingSerializationOperator(blueprint);

    loop(creation_operator, combination_operator, perturbation_operator, serialization_operator);
}

void cgp() {

    int rows = 10;
    int cols =10;
    double perturbation_rate = 0.1;

    auto blueprint = new CartesianGeneticProgrammingGenotypeBlueprint(
        rows,
        cols,
        new CGPFunctionsIndex(),
        -1,
        1
    );
    blueprint->setInputs({"x", "y", "z", "w"});
    auto creation_operator = new CartesianGeneticProgrammingCreationOperator(blueprint);
    auto combination_operator = new CartesianGeneticProgrammingCombinationOperator(blueprint);
    auto perturbation_operator = new CartesianGeneticProgrammingPerturbationOperator(blueprint, perturbation_rate);
    auto serialization_operator = new CartesianGeneticProgrammingSerializationOperator(blueprint);

    loop(creation_operator, combination_operator, perturbation_operator, serialization_operator);
}

void sbgp() {

    int number_of_instructions = 500;
    double initialization_chance_of_nop = 0.5;
    double push_constant_share = 0.1;
    double push_param_share = 0.4;
    double perturbation_chance_of_nop = 0.4;
    double perturbation_rate = 0.2;

    auto blueprint = new StackBasedGeneticProgrammingGenotypeBlueprint(
        number_of_instructions,
        initialization_chance_of_nop,
        push_constant_share,
        push_param_share,
        -1,
        1
    );
    blueprint->setInputs({"x", "y", "z", "w"});

    auto creation_operator = new StackBasedGeneticProgrammingCreationOperator(blueprint);
    auto combination_operator = new StackBasedGeneticProgrammingCombinationOperator(blueprint);
    auto perturbation_operator = new StackBasedGeneticProgrammingPerturbationOperator(blueprint, perturbation_rate, perturbation_chance_of_nop);
    auto serialization_operator = new StackBasedGeneticProgrammingSerializationOperator(blueprint);

    loop(creation_operator, combination_operator, perturbation_operator, serialization_operator);
}

void lgp() {

    auto register_initialization_strategy = new LGPRegisterInitializationStrategyCircularLoading();
    int number_of_registers = 20;
    int number_of_instructions = 500;
    double initialization_chance_of_nop = 0.2;
    double perturbation_chance_of_nop = 0.1;
    double perturbation_rate = 0.1;

    auto blueprint = new LinearGeneticProgrammingGenotypeBlueprint(
        register_initialization_strategy,
        number_of_registers,
        number_of_instructions,
        initialization_chance_of_nop,
        -1,
        1
    );
    blueprint->setInputs({"x", "y", "z", "w"});

    auto creation_operator = new LinearGeneticProgrammingCreationOperator(blueprint);
    auto combination_operator = new LinearGeneticProgrammingCombinationOperator(blueprint);
    auto perturbation_operator = new LinearGeneticProgrammingPerturbationOperator(blueprint, perturbation_rate, perturbation_chance_of_nop);
    auto serialization_operator = new LinearGeneticProgrammingSerializationOperator(blueprint);

    loop(creation_operator, combination_operator, perturbation_operator, serialization_operator);
}

void gep() {

    int head_size = 50;
    double tail_chance_of_param = 0.5;
    double perturbation_rate = 0.2;
    double chance_of_transposition = 1;
    int transposition_max_length = 5;

    auto blueprint = new GeneExpressionProgrammingGenotypeBlueprint(
        head_size,
        tail_chance_of_param,
        -1,
        1
    );
    blueprint->setInputs({"x", "y", "z", "w"});

    auto creation_operator = new GeneExpressionProgrammingCreationOperator(blueprint);
    auto combination_operator = new GeneExpressionProgrammingCombinationOperator(blueprint);
    auto perturbation_operator = new GeneExpressionProgrammingPerturbationOperator(blueprint, perturbation_rate, chance_of_transposition, transposition_max_length);
    auto serialization_operator = new GeneExpressionProgrammingSerializationOperator(blueprint);

    loop(creation_operator, combination_operator, perturbation_operator, serialization_operator);
}

void mep() {

    int number_of_instructions = 200;
    double perturbation_rate = 0.2;

    auto blueprint = new MultiExpressionProgrammingGenotypeBlueprint(
        number_of_instructions,
        -1,
        1
    );
    blueprint->setInputs({"x", "y", "z", "w"});

    auto creation_operator = new MultiExpressionProgrammingCreationOperator(blueprint);
    auto combination_operator = new MultiExpressionProgrammingCombinationOperator(blueprint);
    auto perturbation_operator = new MultiExpressionProgrammingPerturbationOperator(blueprint, perturbation_rate);
    auto serialization_operator = new MultiExpressionProgrammingSerializationOperator(blueprint);

    loop(creation_operator, combination_operator, perturbation_operator, serialization_operator);
}

void ge() {

    int codons = 20;
    int max_number_of_wrapping = 3;
    double perturbation_rate = 0.2;

    auto blueprint = new GrammaticalEvolutionGenotypeBlueprint(
        codons,
        256,
        max_number_of_wrapping,
        -1,
        1
    );
    blueprint->setInputs({"x", "y", "z", "w"});

    auto creation_operator = new GrammaticalEvolutionCreationOperator(blueprint);
    auto combination_operator = new GrammaticalEvolutionCombinationOperator(blueprint);
    auto perturbation_operator = new GrammaticalEvolutionPerturbationOperator(blueprint, perturbation_rate);
    auto serialization_operator = new GrammaticalEvolutionSerializationOperator(blueprint);

    loop(creation_operator, combination_operator, perturbation_operator, serialization_operator);
}

void sge() {

    int max_depth = 5;
    auto perturbation_rate = 0.2;

    auto blueprint = new StructuredGrammaticalEvolutionGenotypeBlueprint(
        max_depth,
        -1,
        1
    );
    blueprint->setInputs({"x", "y", "z", "w"});

    auto creation_operator = new StructuredGrammaticalEvolutionCreationOperator(blueprint);
    auto combination_operator = new StructuredGrammaticalEvolutionCombinationOperator(blueprint);
    auto perturbation_operator = new StructuredGrammaticalEvolutionPerturbationOperator(blueprint, perturbation_rate);
    auto serialization_operator = new StructuredGrammaticalEvolutionSerializationOperator(blueprint);

    loop(creation_operator, combination_operator, perturbation_operator, serialization_operator);
}

void gbgp() {

    int max_number_of_nodes = 200;
    double perturbation_rate = 0.2;
    int max_nodes_to_delete = 5;
    int max_nodes_to_insert = 5;
    int max_number_of_nodes_to_crossover = 10;
    double proceed_in_branch_chance = 0.8;

    auto blueprint = new GraphBasedGeneticProgrammingGenotypeBlueprint(max_number_of_nodes, -1, 1);
    blueprint->setInputs({"x", "y", "z", "w"});

    auto creation_operator = new GraphBasedGeneticProgrammingCreationOperator(blueprint);
    auto combination_operator = new GraphBasedGeneticProgrammingCombinationOperator(
        blueprint,
        max_number_of_nodes_to_crossover,
        proceed_in_branch_chance
    );
    auto perturbation_operator = new GraphBasedGeneticProgrammingPerturbationOperator(
        blueprint,
        perturbation_rate,
        max_nodes_to_delete,
        max_nodes_to_insert
    );
    auto serialization_operator = new GraphBasedGeneticProgrammingSerializationOperator(blueprint);

    loop(creation_operator, combination_operator, perturbation_operator, serialization_operator);
}

int main() {
    // cp();
    // rp();
    // nn();
    tbgp();
    // cgp();
    // lgp();
    // sbgp();
    // gep();
    // mep();
    // ge();
    // sge();
    // gbgp();
}