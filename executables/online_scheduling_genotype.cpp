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
    auto blueprint = new NeuralNetworkGenotypeBlueprint(new NormalDistribution(0, 1), {2, 4, 6});
    auto creation_operator = new NeuralNetworkCreationOperator(blueprint);
    auto combination_operator = new NeuralNetworkCombinationOperator();
    auto perturbation_operator = new NeuralNetworkPerturbationOperator(new NormalDistribution(0, 1));
    auto serialization_operator = new NeuralNetworkSerializationOperator();

    auto genotype = dynamic_cast<NeuralNetwork*>(creation_operator->create());

    auto serialization = serialization_operator->serialize(genotype);
    auto deserialization = serialization_operator->deserialize(serialization);
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

void online_scheduling_algorithm_cluster() {

    std::string const dir = "../tests/test_04/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    auto sub_blueprint = new NeuralNetworkGenotypeBlueprint(new NormalDistribution(0, 1), {2, 4, 6});
    auto sub_creation_operator = new NeuralNetworkCreationOperator(sub_blueprint);
    auto sub_combination_operator = new NeuralNetworkCombinationOperator();
    auto sub_perturbation_operator = new NeuralNetworkPerturbationOperator(new NormalDistribution(0, 1));
    auto sub_serialization_operator = new NeuralNetworkSerializationOperator();

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
    // neural_network();
    // tree_based_genetic_programming();
    // cartesian_genetic_programming();
    linear_genetic_programming();
    // online_scheduling_algorithm_cluster();
}
