//
// Created by mihael on 5/19/24.
//

#include <iostream>

#include "CartesianGeneticProgramming.h"
#include "CartesianGeneticProgrammingCombinationOperator.h"
#include "CartesianGeneticProgrammingCreationOperator.h"
#include "CartesianGeneticProgrammingGenotypeBlueprint.h"
#include "CartesianGeneticProgrammingPerturbationOperator.h"
#include "CartesianGeneticProgrammingSerializationOperator.h"
#include "ConstantProgramming.h"
#include "ConstantProgrammingCombinationOperator.h"
#include "ConstantProgrammingCreationOperator.h"
#include "ConstantProgrammingGenotypeBlueprint.h"
#include "ConstantProgrammingPerturbationOperator.h"
#include "ConstantProgrammingSerializationOperator.h"
#include "GeneExpressionProgramming.h"
#include "GeneExpressionProgrammingCombinationOperator.h"
#include "GeneExpressionProgrammingCreationOperator.h"
#include "GeneExpressionProgrammingGenotypeBlueprint.h"
#include "GeneExpressionProgrammingPerturbationOperator.h"
#include "GeneExpressionProgrammingSerializationOperator.h"
#include "GrammaticalEvolution.h"
#include "GrammaticalEvolutionCombinationOperator.h"
#include "GrammaticalEvolutionCreationOperator.h"
#include "GrammaticalEvolutionGenotypeBlueprint.h"
#include "GrammaticalEvolutionPerturbationOperator.h"
#include "GrammaticalEvolutionSerializationOperator.h"
#include "GraphBasedGeneticProgramming.h"
#include "GraphBasedGeneticProgrammingCombinationOperator.h"
#include "GraphBasedGeneticProgrammingCreationOperator.h"
#include "GraphBasedGeneticProgrammingGenotypeBlueprint.h"
#include "GraphBasedGeneticProgrammingPerturbationOperator.h"
#include "GraphBasedGeneticProgrammingSerializationOperator.h"
#include "JobSpecificationsParser.h"
#include "LGPRegisterInitializationStrategyCircularLoading.h"
#include "LGPRegisterInitializationStrategyEmptyLoading.h"
#include "LGPRegisterInitializationStrategySingularLoading.h"
#include "LinearGeneticProgramming.h"
#include "LinearGeneticProgrammingCombinationOperator.h"
#include "LinearGeneticProgrammingCreationOperator.h"
#include "LinearGeneticProgrammingGenotypeBlueprint.h"
#include "LinearGeneticProgrammingPerturbationOperator.h"
#include "LinearGeneticProgrammingSerializationOperator.h"
#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "MachineTypeMap.h"
#include "MultiExpressionProgramming.h"
#include "MultiExpressionProgrammingCombinationOperator.h"
#include "MultiExpressionProgrammingCreationOperator.h"
#include "MultiExpressionProgrammingGenotypeBlueprint.h"
#include "MultiExpressionProgrammingPerturbationOperator.h"
#include "MultiExpressionProgrammingSerializationOperator.h"
#include "NeuralNetwork.h"
#include "NeuralNetworkCombinationOperator.h"
#include "NeuralNetworkCreationOperator.h"
#include "NeuralNetworkGenotypeBlueprint.h"
#include "NeuralNetworkPerturbationOperator.h"
#include "NeuralNetworkSerializationOperator.h"
#include "NormalDistribution.h"
#include "OnlineSchedulingAlgorithmCluster.h"
#include "OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity.h"
#include "OnlineSchedulingAlgorithmClusterCreationOperator.h"
#include "OnlineSchedulingAlgorithmClusterGenotypeBlueprint.h"
#include "OnlineSchedulingAlgorithmClusterPerturbationOperator.h"
#include "OnlineSchedulingAlgorithmClusterSerializationOperator.h"
#include "RandomProgramming.h"
#include "RandomProgrammingCombinationOperator.h"
#include "RandomProgrammingCreationOperator.h"
#include "RandomProgrammingGenotypeBlueprint.h"
#include "RandomProgrammingPerturbationOperator.h"
#include "RandomProgrammingSerializationOperator.h"
#include "StackBasedGeneticProgramming.h"
#include "StackBasedGeneticProgrammingCombinationOperator.h"
#include "StackBasedGeneticProgrammingCreationOperator.h"
#include "StackBasedGeneticProgrammingGenotypeBlueprint.h"
#include "StackBasedGeneticProgrammingPerturbationOperator.h"
#include "StackBasedGeneticProgrammingSerializationOperator.h"
#include "StructuredGrammaticalEvolution.h"
#include "StructuredGrammaticalEvolutionCombinationOperator.h"
#include "StructuredGrammaticalEvolutionCreationOperator.h"
#include "StructuredGrammaticalEvolutionGenotypeBlueprint.h"
#include "StructuredGrammaticalEvolutionPerturbationOperator.h"
#include "StructuredGrammaticalEvolutionSerializationOperator.h"
#include "TBGPNodeFactory.h"
#include "Topology.h"
#include "TreeBasedGeneticProgrammingCombinationOperator.h"
#include "TreeBasedGeneticProgrammingCreationOperator.h"
#include "TreeBasedGeneticProgrammingGenotypeBlueprint.h"
#include "TreeBasedGeneticProgrammingPerturbationOperator.h"
#include "TreeBasedGeneticProgrammingSerializationOperator.h"

void constant_programming() {
    auto blueprint = new ConstantProgrammingGenotypeBlueprint(0);
    auto creation_operator = new ConstantProgrammingCreationOperator(blueprint);
    auto combination_operator = new ConstantProgrammingCombinationOperator();
    auto perturbation_operator = new ConstantProgrammingPerturbationOperator();
    auto serialization_operator = new ConstantProgrammingSerializationOperator();

    auto genotype = dynamic_cast<ConstantProgramming*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(genotype);
    auto deserialization = serialization_operator->deserialize(serialization);

    for (int i = 0; i < 100000000; i++) {
        std::cout << i << std::endl;

        auto x = creation_operator->create();
        auto a = serialization_operator->serialize(x);
        auto y = serialization_operator->deserialize(a);
        auto b = serialization_operator->serialize(y);

        if (a.size() != b.size()) {
            throw;
        }
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                throw;
            }
        }

        delete x;
        delete y;
    }
}

void random_programming() {
    auto blueprint = new RandomProgrammingGenotypeBlueprint(0, 1);
    auto creation_operator = new RandomProgrammingCreationOperator(blueprint);
    auto combination_operator = new RandomProgrammingCombinationOperator();
    auto perturbation_operator = new RandomProgrammingPerturbationOperator();
    auto serialization_operator = new RandomProgrammingSerializationOperator();

    auto genotype = dynamic_cast<RandomProgramming*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(genotype);
    auto deserialization = serialization_operator->deserialize(serialization);
}

void neural_network() {
    auto blueprint = new NeuralNetworkGenotypeBlueprint(new NormalDistribution(0, 1), {1}, "sigm");
    auto creation_operator = new NeuralNetworkCreationOperator(blueprint);
    auto combination_operator = new NeuralNetworkCombinationOperator();
    auto perturbation_operator = new NeuralNetworkPerturbationOperator(new NormalDistribution(0, 1));
    auto serialization_operator = new NeuralNetworkSerializationOperator(blueprint);

    auto genotype = dynamic_cast<NeuralNetwork*>(creation_operator->create());

    blueprint->setInputs({"x", "y", "z", "w"});
    std::map<std::string, double> params;
    params["x"] = 1;
    params["y"] = -1;
    params["z"] = 0.5;
    params["w"] = -0.5;

    auto gbgp1 = dynamic_cast<GraphBasedGeneticProgramming*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(gbgp1);
    for (const auto& line : serialization) {
        std::cout << line << std::endl;
    }
    auto deserialization = serialization_operator->deserialize(serialization);

    std::cout << std::endl;
    for (const auto& line : serialization_operator->serialize(deserialization)) {
        std::cout << line << std::endl;
    }

    std::cout << std::endl;
    std::cout << "val = " << gbgp1->calculateScore(params) << std::endl;

    auto gbgp2 = dynamic_cast<GraphBasedGeneticProgramming*>(creation_operator->create());

    auto gbgp = dynamic_cast<GraphBasedGeneticProgramming*>(combination_operator->combine(gbgp1, gbgp2));
    perturbation_operator->perturbate(gbgp);

    std::cout << "val = " << gbgp->calculateScore(params) << std::endl;
}

void tree_based_genetic_programming() {

    std::string const dir = "../experiments/experiment_99/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    double leaf_const_chance = 0.1;
    double leaf_param_chance = 0.3;
    int max_height = 10;

    auto sub_node_factory = new TBGPNodeFactory(leaf_const_chance, leaf_param_chance, -1, 1);
    auto sub_blueprint = new TreeBasedGeneticProgrammingGenotypeBlueprint(sub_node_factory, max_height);
    auto sub_creation_operator = new TreeBasedGeneticProgrammingCreationOperator(sub_blueprint);
    auto sub_combination_operator = new TreeBasedGeneticProgrammingCombinationOperator(sub_blueprint);
    auto sub_perturbation_operator = new TreeBasedGeneticProgrammingPerturbationOperator(sub_blueprint);
    auto sub_serialization_operator = new TreeBasedGeneticProgrammingSerializationOperator(sub_blueprint);

    auto blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        blueprint,
        sub_creation_operator
    );
    auto combination_operator = new OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(
        sub_combination_operator
    );
    auto perturbation_operator =new OnlineSchedulingAlgorithmClusterPerturbationOperator(
        sub_perturbation_operator
    );
    auto serialization_operator = new OnlineSchedulingAlgorithmClusterSerializationOperator(topology, sub_serialization_operator);

    auto genotype = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(genotype);
    for (const auto& line : serialization_operator->serialize(genotype)) {
        std::cout << line << std::endl;
    }
    auto deserialization = serialization_operator->deserialize(serialization);

    std::cout << std::endl;
    for (const auto& line : serialization_operator->serialize(deserialization)) {
        std::cout << line << std::endl;
    }

}

void cartesian_genetic_programming() {

    std::string const dir = "../experiments/experiment_99/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    int rows = 5;
    int cols = 8;
    double perturbation_rate = 0.1;

    auto sub_blueprint = new CartesianGeneticProgrammingGenotypeBlueprint(
        rows,
        cols,
        new CGPFunctionsIndex(),
        -1,
        1
    );
    auto sub_creation_operator = new CartesianGeneticProgrammingCreationOperator(sub_blueprint);
    auto sub_combination_operator = new CartesianGeneticProgrammingCombinationOperator(sub_blueprint);
    auto sub_perturbation_operator = new CartesianGeneticProgrammingPerturbationOperator(sub_blueprint, perturbation_rate);
    auto sub_serialization_operator = new CartesianGeneticProgrammingSerializationOperator(sub_blueprint);

    auto blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        blueprint,
        sub_creation_operator
    );
    auto combination_operator = new OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(
        sub_combination_operator
    );
    auto perturbation_operator =new OnlineSchedulingAlgorithmClusterPerturbationOperator(
        sub_perturbation_operator
    );
    auto serialization_operator = new OnlineSchedulingAlgorithmClusterSerializationOperator(topology, sub_serialization_operator);

    auto genotype = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(genotype);
    for (const auto& line : serialization_operator->serialize(genotype)) {
        std::cout << line << std::endl;
    }
    auto deserialization = serialization_operator->deserialize(serialization);

    std::cout << std::endl;
    for (const auto& line : serialization_operator->serialize(deserialization)) {
        std::cout << line << std::endl;
    }

    sub_blueprint->setInputs(OnlineSchedulingAlgorithm::group_inputs);

    auto cgp1 = dynamic_cast<CartesianGeneticProgramming*>(sub_creation_operator->create());
    auto cgp2 = dynamic_cast<CartesianGeneticProgramming*>(sub_creation_operator->create());
    auto cgp = sub_combination_operator->combine(cgp1, cgp2);
    sub_perturbation_operator->perturbate(cgp);
}

void linear_genetic_programming() {

    std::string const dir = "../experiments/experiment_99/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    auto register_initialization_strategy = new LGPRegisterInitializationStrategyCircularLoading();
    int number_of_registers = 10;
    int number_of_instructions = 500;
    double initialization_chance_of_nop = 0.2;
    double perturbation_chance_of_nop = 0.1;
    double perturbation_rate = 0.1;

    auto sub_blueprint = new LinearGeneticProgrammingGenotypeBlueprint(
        register_initialization_strategy,
        number_of_registers,
        number_of_instructions,
        initialization_chance_of_nop,
        -1,
        1
    );

    auto sub_creation_operator = new LinearGeneticProgrammingCreationOperator(sub_blueprint);
    auto sub_combination_operator = new LinearGeneticProgrammingCombinationOperator(sub_blueprint);
    auto sub_perturbation_operator = new LinearGeneticProgrammingPerturbationOperator(sub_blueprint, perturbation_rate, perturbation_chance_of_nop);
    auto sub_serialization_operator = new LinearGeneticProgrammingSerializationOperator(sub_blueprint);

    auto blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        blueprint,
        sub_creation_operator
    );
    auto combination_operator = new OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(
        sub_combination_operator
    );
    auto perturbation_operator =new OnlineSchedulingAlgorithmClusterPerturbationOperator(
        sub_perturbation_operator
    );
    auto serialization_operator = new OnlineSchedulingAlgorithmClusterSerializationOperator(topology, sub_serialization_operator);

    auto genotype = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(genotype);
    for (const auto& line : serialization_operator->serialize(genotype)) {
        std::cout << line << std::endl;
    }
    auto deserialization = serialization_operator->deserialize(serialization);

    std::cout << std::endl;
    for (const auto& line : serialization_operator->serialize(deserialization)) {
        std::cout << line << std::endl;
    }

    sub_blueprint->setInputs({"x", "y"});
    std::map<std::string, double> params;
    params["x"] = 1;
    params["y"] = -1;

    auto lgp1 = dynamic_cast<LinearGeneticProgramming*>(sub_creation_operator->create());
    auto lgp2 = dynamic_cast<LinearGeneticProgramming*>(sub_creation_operator->create());

    auto val = lgp1->calculateScore(params);
    std::cout << val << std::endl;

    auto lgp = sub_combination_operator->combine(lgp1, lgp2);
    sub_perturbation_operator->perturbate(lgp);
}

void stack_based_genetic_programming() {

    std::string const dir = "../experiments/experiment_99/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    int number_of_instructions = 100;
    double initialization_chance_of_nop = 0.5;
    double push_constant_share = 0.1;
    double push_param_share = 0.4;
    double perturbation_chance_of_nop = 0.4;
    double perturbation_rate = 0.2;

    auto sub_blueprint = new StackBasedGeneticProgrammingGenotypeBlueprint(
        number_of_instructions,
        initialization_chance_of_nop,
        push_constant_share,
        push_param_share,
        -1,
        1
    );

    auto sub_creation_operator = new StackBasedGeneticProgrammingCreationOperator(sub_blueprint);
    auto sub_combination_operator = new StackBasedGeneticProgrammingCombinationOperator(sub_blueprint);
    auto sub_perturbation_operator = new StackBasedGeneticProgrammingPerturbationOperator(sub_blueprint, perturbation_rate, perturbation_chance_of_nop);
    auto sub_serialization_operator = new StackBasedGeneticProgrammingSerializationOperator(sub_blueprint);

    auto blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        blueprint,
        sub_creation_operator
    );
    auto combination_operator = new OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(
        sub_combination_operator
    );
    auto perturbation_operator =new OnlineSchedulingAlgorithmClusterPerturbationOperator(
        sub_perturbation_operator
    );
    auto serialization_operator = new OnlineSchedulingAlgorithmClusterSerializationOperator(topology, sub_serialization_operator);

    auto genotype = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(genotype);
    for (const auto& line : serialization_operator->serialize(genotype)) {
        std::cout << line << std::endl;
    }
    auto deserialization = serialization_operator->deserialize(serialization);

    std::cout << std::endl;
    for (const auto& line : serialization_operator->serialize(deserialization)) {
        std::cout << line << std::endl;
    }

    sub_blueprint->setInputs({"x", "y"});
    std::map<std::string, double> params;
    params["x"] = 1;
    params["y"] = -1;

    auto sbgp1 = dynamic_cast<StackBasedGeneticProgramming*>(sub_creation_operator->create());
    auto sbgp2 = dynamic_cast<StackBasedGeneticProgramming*>(sub_creation_operator->create());

    auto val = sbgp1->calculateScore(params);
    std::cout << val << std::endl;

    auto sbgp = sub_combination_operator->combine(sbgp1, sbgp2);
    sub_perturbation_operator->perturbate(sbgp);
}

void gene_expression_programming() {
    std::string const dir = "../experiments/experiment_99/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    int head_size = 50;
    double tail_chance_of_param = 0.5;
    double perturbation_rate = 0.2;
    double chance_of_transposition = 1;
    int transposition_max_length = 5;

    auto sub_blueprint = new GeneExpressionProgrammingGenotypeBlueprint(
        head_size,
        tail_chance_of_param,
        -1,
        1
    );

    auto sub_creation_operator = new GeneExpressionProgrammingCreationOperator(sub_blueprint);
    auto sub_combination_operator = new GeneExpressionProgrammingCombinationOperator(sub_blueprint);
    auto sub_perturbation_operator = new GeneExpressionProgrammingPerturbationOperator(sub_blueprint, perturbation_rate, chance_of_transposition, transposition_max_length);
    auto sub_serialization_operator = new GeneExpressionProgrammingSerializationOperator(sub_blueprint);

    auto blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        blueprint,
        sub_creation_operator
    );
    auto combination_operator = new OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(
        sub_combination_operator
    );
    auto perturbation_operator =new OnlineSchedulingAlgorithmClusterPerturbationOperator(
        sub_perturbation_operator
    );
    auto serialization_operator = new OnlineSchedulingAlgorithmClusterSerializationOperator(topology, sub_serialization_operator);

    auto genotype = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(genotype);
    for (const auto& line : serialization_operator->serialize(genotype)) {
    std::cout << line << std::endl;
    }
    auto deserialization = serialization_operator->deserialize(serialization);

    std::cout << std::endl;
        for (const auto& line : serialization_operator->serialize(deserialization)) {
        std::cout << line << std::endl;
    }

    sub_blueprint->setInputs({"x", "y"});
    std::map<std::string, double> params;
    params["x"] = 1;
    params["y"] = -1;

    auto gep1 = dynamic_cast<GeneExpressionProgramming*>(sub_creation_operator->create());

    // for (const auto& line : sub_serialization_operator->serialize(gep1)) {
    //     std::cout << line << std::endl;
    // }
    // std::cout << std::endl;
    // for (const auto& line : sub_serialization_operator->serializePhenotype(gep1)) {
    //     std::cout << line << std::endl;
    // }

    auto gep2 = dynamic_cast<GeneExpressionProgramming*>(sub_creation_operator->create());

    auto val = gep1->calculateScore(params);
    std::cout << val << std::endl;

    auto gep = sub_combination_operator->combine(gep1, gep2);
    sub_perturbation_operator->perturbate(gep);

    std::cout << dynamic_cast<GeneExpressionProgramming*>(gep)->calculateScore(params) << std::endl;
}

void multi_expression_programming() {

    std::string const dir = "../experiments/experiment_99/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    int number_of_instructions = 200;
    double perturbation_rate = 0.2;

    auto sub_blueprint = new MultiExpressionProgrammingGenotypeBlueprint(
        number_of_instructions,
        -1,
        1
    );

    auto sub_creation_operator = new MultiExpressionProgrammingCreationOperator(sub_blueprint);
    auto sub_combination_operator = new MultiExpressionProgrammingCombinationOperator(sub_blueprint);
    auto sub_perturbation_operator = new MultiExpressionProgrammingPerturbationOperator(sub_blueprint, perturbation_rate);
    auto sub_serialization_operator = new MultiExpressionProgrammingSerializationOperator(sub_blueprint);

    auto blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        blueprint,
        sub_creation_operator
    );
    auto combination_operator = new OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(
        sub_combination_operator
    );
    auto perturbation_operator =new OnlineSchedulingAlgorithmClusterPerturbationOperator(
        sub_perturbation_operator
    );
    auto serialization_operator = new OnlineSchedulingAlgorithmClusterSerializationOperator(topology, sub_serialization_operator);

    auto genotype = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(genotype);
    for (const auto& line : serialization_operator->serialize(genotype)) {
        std::cout << line << std::endl;
    }
    auto deserialization = serialization_operator->deserialize(serialization);

    std::cout << std::endl;
    for (const auto& line : serialization_operator->serialize(deserialization)) {
        std::cout << line << std::endl;
    }

    sub_blueprint->setInputs({"x", "y"});
    std::map<std::string, double> params;
    params["x"] = 1;
    params["y"] = -1;

    auto mep1 = dynamic_cast<MultiExpressionProgramming*>(sub_creation_operator->create());
    auto mep2 = dynamic_cast<MultiExpressionProgramming*>(sub_creation_operator->create());

    auto val = mep1->calculateScore(params);
    std::cout << val << std::endl;

    auto mep = sub_combination_operator->combine(mep1, mep2);
    sub_perturbation_operator->perturbate(mep);
}

void grammatical_evolution() {

    std::string const dir = "../experiments/experiment_99/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    int codons = 200;
    int max_number_of_wrapping = 3;
    double perturbation_rate = 0.2;

    auto sub_blueprint = new GrammaticalEvolutionGenotypeBlueprint(
        codons,
        256,
        max_number_of_wrapping,
        -1,
        1
    );

    auto sub_creation_operator = new GrammaticalEvolutionCreationOperator(sub_blueprint);
    auto sub_combination_operator = new GrammaticalEvolutionCombinationOperator(sub_blueprint);
    auto sub_perturbation_operator = new GrammaticalEvolutionPerturbationOperator(sub_blueprint, perturbation_rate);
    auto sub_serialization_operator = new GrammaticalEvolutionSerializationOperator(sub_blueprint);

    auto blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        blueprint,
        sub_creation_operator
    );
    auto combination_operator = new OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(
        sub_combination_operator
    );
    auto perturbation_operator =new OnlineSchedulingAlgorithmClusterPerturbationOperator(
        sub_perturbation_operator
    );
    auto serialization_operator = new OnlineSchedulingAlgorithmClusterSerializationOperator(topology, sub_serialization_operator);

    auto genotype = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(genotype);
    for (const auto& line : serialization_operator->serialize(genotype)) {
        std::cout << line << std::endl;
    }
    auto deserialization = serialization_operator->deserialize(serialization);

    std::cout << std::endl;
        for (const auto& line : serialization_operator->serialize(deserialization)) {
        std::cout << line << std::endl;
    }

    sub_blueprint->setInputs({"x", "y"});
    std::map<std::string, double> params;
    params["x"] = 1;
    params["y"] = -1;

    auto ge1 = dynamic_cast<GrammaticalEvolution*>(sub_creation_operator->create());

    // for (const auto& line : sub_serialization_operator->serialize(ge1)) {
    //     std::cout << line << std::endl;
    // }
    // std::cout << std::endl;
    // for (const auto& line : sub_serialization_operator->serializePhenotype(ge1)) {
    //     std::cout << line << std::endl;
    // }

    auto ge2 = dynamic_cast<GrammaticalEvolution*>(sub_creation_operator->create());

    auto val = ge1->calculateScore(params);
    std::cout << val << std::endl;

    auto ge = sub_combination_operator->combine(ge1, ge2);
    sub_perturbation_operator->perturbate(ge);

    std::cout << dynamic_cast<GrammaticalEvolution*>(ge)->calculateScore(params) << std::endl;

    for (int i = 0; i < 1000000; i++) {
        std::cout << i << std::endl;

        auto x = sub_creation_operator->create();
        auto a = sub_serialization_operator->serialize(x);
        auto y = sub_serialization_operator->deserialize(a);
        auto b = sub_serialization_operator->serialize(y);

        if (a.size() != b.size()) {
            throw;
        }
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                throw;
            }
        }

        delete x;
        delete y;
    }
}

void structured_grammatical_evolution() {
    std::string const dir = "../experiments/experiment_99/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    int max_depth = 5;
    auto perturbation_rate = 0.2;

    auto sub_blueprint = new StructuredGrammaticalEvolutionGenotypeBlueprint(
        max_depth,
        -1,
        1
    );

    auto sub_creation_operator = new StructuredGrammaticalEvolutionCreationOperator(sub_blueprint);
    auto sub_combination_operator = new StructuredGrammaticalEvolutionCombinationOperator(sub_blueprint);
    auto sub_perturbation_operator = new StructuredGrammaticalEvolutionPerturbationOperator(sub_blueprint, perturbation_rate);
    auto sub_serialization_operator = new StructuredGrammaticalEvolutionSerializationOperator(sub_blueprint);

    auto blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        blueprint,
        sub_creation_operator
    );
    auto combination_operator = new OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(
        sub_combination_operator
    );
    auto perturbation_operator =new OnlineSchedulingAlgorithmClusterPerturbationOperator(
        sub_perturbation_operator
    );
    auto serialization_operator = new OnlineSchedulingAlgorithmClusterSerializationOperator(topology, sub_serialization_operator);

    auto genotype = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(genotype);
    for (const auto& line : serialization_operator->serialize(genotype)) {
        std::cout << line << std::endl;
    }
    auto deserialization = serialization_operator->deserialize(serialization);

    std::cout << std::endl;
        for (const auto& line : serialization_operator->serialize(deserialization)) {
        std::cout << line << std::endl;
    }

    sub_blueprint->setInputs({"x", "y", "z", "w"});
    std::map<std::string, double> params;
    params["x"] = 1;
    params["y"] = -1;
    params["z"] = 0.5;
    params["w"] = -0.5;

    auto sge1 = dynamic_cast<StructuredGrammaticalEvolution*>(sub_creation_operator->create());

    std::cout << std::endl;
    for (const auto& line : sub_serialization_operator->serialize(sge1)) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
    for (const auto& line : sub_serialization_operator->serializePhenotype(sge1)) {
        std::cout << line << std::endl;
    }

    auto sge2 = dynamic_cast<StructuredGrammaticalEvolution*>(sub_creation_operator->create());

    auto val = sge1->calculateScore(params);
    std::cout << val << std::endl;

    auto sge = sub_combination_operator->combine(sge1, sge2);
    sub_perturbation_operator->perturbate(sge);

    std::cout << dynamic_cast<StructuredGrammaticalEvolution*>(sge)->calculateScore(params) << std::endl;
}

void graph_based_genetic_programming() {
    int max_number_of_nodes = 200;
    double perturbation_rate = 0.2;
    int max_nodes_to_delete = 5;
    int max_nodes_to_insert = 5;
    int max_number_of_nodes_to_crossover = 10;
    double proceed_in_branch_chance = 0.8;

    auto blueprint = new GraphBasedGeneticProgrammingGenotypeBlueprint(max_number_of_nodes, -1, 1);

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

    blueprint->setInputs({"x", "y", "z", "w"});
    std::map<std::string, double> params;
    params["x"] = 1;
    params["y"] = -1;
    params["z"] = 0.5;
    params["w"] = -0.5;

    auto gbgp1 = dynamic_cast<GraphBasedGeneticProgramming*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(gbgp1);
    for (const auto& line : serialization) {
        std::cout << line << std::endl;
    }
    auto deserialization = serialization_operator->deserialize(serialization);

    std::cout << std::endl;
    for (const auto& line : serialization_operator->serialize(deserialization)) {
        std::cout << line << std::endl;
    }

    std::cout << std::endl;
    std::cout << "val = " << gbgp1->calculateScore(params) << std::endl;

    auto gbgp2 = dynamic_cast<GraphBasedGeneticProgramming*>(creation_operator->create());

    auto gbgp = dynamic_cast<GraphBasedGeneticProgramming*>(combination_operator->combine(gbgp1, gbgp2));
    perturbation_operator->perturbate(gbgp);

    std::cout << "val = " << gbgp->calculateScore(params) << std::endl;
}

void online_scheduling_algorithm_cluster() {

    std::string const dir = "../tests/test_04/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    auto sub_blueprint = new NeuralNetworkGenotypeBlueprint(new NormalDistribution(0, 1), {2, 4, 6}, "sigm");
    auto sub_creation_operator = new NeuralNetworkCreationOperator(sub_blueprint);
    auto sub_combination_operator = new NeuralNetworkCombinationOperator();
    auto sub_perturbation_operator = new NeuralNetworkPerturbationOperator(new NormalDistribution(0, 1));
    auto sub_serialization_operator = new NeuralNetworkSerializationOperator(sub_blueprint);

    auto blueprint = new OnlineSchedulingAlgorithmClusterGenotypeBlueprint(topology);
    auto creation_operator = new OnlineSchedulingAlgorithmClusterCreationOperator(
        blueprint,
        sub_creation_operator
    );
    auto combination_operator = new OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity(
        sub_combination_operator
    );
    auto perturbation_operator =new OnlineSchedulingAlgorithmClusterPerturbationOperator(
        sub_perturbation_operator
    );
    auto serialization_operator = new OnlineSchedulingAlgorithmClusterSerializationOperator(topology, sub_serialization_operator);

    auto genotype = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(genotype);
    auto deserialization = serialization_operator->deserialize(serialization);
}

int main() {
    // constant_programming();
    // random_programming();
    neural_network();
    // tree_based_genetic_programming();
    // cartesian_genetic_programming();
    // linear_genetic_programming();
    // stack_based_genetic_programming();
    // gene_expression_programming();
    // multi_expression_programming();
    // grammatical_evolution();
    // structured_grammatical_evolution();
    // graph_based_genetic_programming();
    // online_scheduling_algorithm_cluster();
}
