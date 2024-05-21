//
// Created by mihael on 5/20/24.
//

#include <iostream>
#include <string>

#include "BasicTopologyEnumerator.h"
#include "Job.h"
#include "JobSequenceParser.h"
#include "JobSpecificationsParser.h"
#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "MachineTypeMap.h"
#include "NeuralNetworkCombinationOperator.h"
#include "NeuralNetworkCreationOperator.h"
#include "NeuralNetworkGenotypeBlueprint.h"
#include "NeuralNetworkPerturbationOperator.h"
#include "NeuralNetworkSerializationOperator.h"
#include "NormalDistribution.h"
#include "OnlineSchedulingAlgorithmClusterCombinationOperatorWithCoarseGranularity.h"
#include "OnlineSchedulingAlgorithmClusterCreationOperator.h"
#include "OnlineSchedulingAlgorithmClusterGenotypeBlueprint.h"
#include "OnlineSchedulingAlgorithmClusterPerturbationOperator.h"
#include "OnlineSchedulingAlgorithmClusterSerializationOperator.h"
#include "SchedulingEvaluationFunction.h"
#include "SteadyStateGeneticAlgorithm.h"
#include "Topology.h"
#include "TotalWeightedCompletionTimeObjectiveFunction.h"

int main() {
    std::string const dir = "../experiments/experiment_01/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    std::map<long, Job*> jobs = JobSequenceParser::parse(dir + "job_sequence.yaml", machine_type_map, job_type_map, topology);

    int population_size = 20;
    int iterations_count = 1000;

    auto objective_function = new TotalWeightedCompletionTimeObjectiveFunction();
    auto evaluation_function = new SchedulingEvaluationFunction(
        objective_function,
        topology,
        jobs,
        true,
        dir + "output/logs/"
    );

    auto sub_blueprint = new NeuralNetworkGenotypeBlueprint(new NormalDistribution(0, 0.01), {1});
    auto sub_creation_operator = new NeuralNetworkCreationOperator(sub_blueprint);
    auto sub_combination_operator = new NeuralNetworkCombinationOperator();
    auto sub_perturbation_operator = new NeuralNetworkPerturbationOperator(new NormalDistribution(0, 0.01));
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
    auto topology_enumerator = new BasicTopologyEnumerator(topology);
    auto machines_partition = topology_enumerator->getPartition();
    combination_operator->setModifiableMachines(machines_partition);
    perturbation_operator->setModifiableMachines(machines_partition);

    auto algorithm = new SteadyStateGeneticAlgorithm(
        evaluation_function,
        creation_operator,
        perturbation_operator,
        combination_operator,
        population_size,
        iterations_count
    );
    auto population = new Population(population_size);
    algorithm->optimize(population);

    for (auto line : serialization_operator->serialize(population->getGenotype(0)->genotype)) {
        std::cout << line << std::endl;
    }
}
