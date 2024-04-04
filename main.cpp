#include "BitSumCombinationOperator.h"
#include "BitSumCreationOperator.h"
#include "BitSumEvaluationFunction.h"
#include "BitSumGenotypeBlueprint.h"
#include "BitSumPerturbationOperator.h"
#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "JobSpecificationsParser.h"
#include "JobSequenceParser.h"
#include "GenotypeDeserializer.h"
#include "GenotypeSerializer.h"
#include "Simulator.h"
#include "TopologyUtils.h"
#include "PathNodeUtils.h"
#include "PathTreeNodeUtils.h"
#include "set"
#include "filesystem"
#include "iostream"
#include "MakespanObjectiveFunction.h"
#include "SteadyStateGeneticAlgorithm.h"

void run_example(const std::string& dir) {

    std::cout << "Running " << dir << std::endl;

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);
    TopologyUtils::logTopology(topology, dir + "output/topology.txt");

    std::map<long, Job*> jobs = JobSequenceParser::parse(dir + "job_sequence.yaml", machine_type_map, job_type_map, topology);
    PathNodeUtils::logPathNodes(jobs, dir + "output/path_nodes.txt");
    PathTreeNodeUtils::logPathTreeNodes(jobs, dir + "output/path_tree_nodes.txt");

    Individual* individual = GenotypeDeserializer::deserialize(dir + "individual.yaml", topology, jobs);
    GenotypeSerializer::serialize(dir + "output/individual.yaml", individual);

    auto statistics = Simulator::simulate(individual, topology, jobs, true, dir + "output/simulator_logs.txt");
    auto objective_function = MakespanObjectiveFunction();
    objective_function.evaluate(statistics);
}

void bit_sum_genotype() {
    int population_size = 200;
    int iterations_count = 10000;
    int number_of_bits = 100;
    double bit_flip_chance = 0.02;

    auto evaluation_function = new BitSumEvaluationFunction(false);
    auto blueprint = new BitSumGenotypeBlueprint(number_of_bits);
    auto creation_operator = new BitSumCreationOperator(blueprint);
    auto perturbation_operator = new BitSumPerturbationOperator(bit_flip_chance);
    auto combination_operator = new BitSumCombinationOperator();
    auto ssga = new SteadyStateGeneticAlgorithm(
        evaluation_function,
        creation_operator,
        perturbation_operator,
        combination_operator,
        population_size,
        iterations_count
    );
    auto solution = ssga->optimize();
}

int main() {
    // std::set<std::string> examples_sorted_by_name;
    // for (const auto& entry : std::filesystem::directory_iterator("../examples/")) {
        // if (entry.is_directory()) {
            // examples_sorted_by_name.insert(entry.path().string() + "/");
        // }
    // }
    // for (const auto& entry : examples_sorted_by_name) {
        // try {
            // run_example(entry);
        // }
        // catch (...) {
            // std::cout << "FAILED" << std::endl;
        // }
    // }
    bit_sum_genotype();
}