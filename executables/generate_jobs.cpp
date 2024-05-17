//
// Created by mihael on 5/5/24.
//

#include "BitSumGenotype.h"
#include "BitSumPerturbationOperator.h"
#include "ExponentialDistribution.h"
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
#include "JobSequenceGenerator.h"
#include "JobSequenceGeneratorSerializer.h"
#include "MakespanObjectiveFunction.h"
#include "OfflineScheduler.h"

int main() {
    std::set<std::string> examples_sorted_by_name;
    for (const auto& entry : std::filesystem::directory_iterator("../examples/")) {
        if (entry.is_directory()) {
            examples_sorted_by_name.insert(entry.path().string() + "/");
        }
    }
    for (const auto& dir : examples_sorted_by_name) {
        try {
            std::cout << "Running " << dir << std::endl;

            MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

            JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
            machine_type_map->constructSetupAndBatchRules(job_type_map);

            Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);
            std::map<long, Job*> jobs = JobSequenceParser::parse(dir + "job_sequence.yaml", machine_type_map, job_type_map, topology);

            std::map<long, JobGeneratorParameters*> job_generator_parameters;
            for (auto [job_type_id, _] : job_type_map->getJobTypeMap()) {
                job_generator_parameters[job_type_id] = new JobGeneratorParameters(
                    job_type_id,
                    100,
                    new ExponentialDistribution(0.2),
                    5,
                    new UniformRealDistributionGenerator(1, 5)
                );
            }
            auto generated_jobs = JobSequenceGenerator::generateJobs(
                job_generator_parameters,
                topology->getRootElement(),
                job_type_map,
                0.5,
                0.5
            );
            JobSequenceGeneratorSerializer::serializeJobs(dir + "output/job_sequence.yaml", generated_jobs);
            JobSequenceParser::parse(dir + "output/job_sequence.yaml", machine_type_map, job_type_map, topology);
        }
        catch (...) {
            std::cout << "FAILED" << std::endl;
        }
    }
}