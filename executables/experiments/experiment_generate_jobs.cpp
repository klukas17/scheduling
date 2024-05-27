//
// Created by mihael on 5/22/24.
//

#include <string>

#include "ExponentialDistribution.h"
#include "JobGeneratorParameters.h"
#include "JobSequenceGenerator.h"
#include "JobSequenceGeneratorSerializer.h"
#include "JobSpecificationsParser.h"
#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "MachineTypeMap.h"
#include "Topology.h"
#include "UniformRealDistributionGenerator.h"

int main() {
    std::string const dir = "../experiments/experiment_00/";

    MachineTypeMap* machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    JobTypeMap* job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    machine_type_map->constructSetupAndBatchRules(job_type_map);

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    std::map<long, JobGeneratorParameters*> job_generator_parameters;

    for (auto [job_type_id, _] : job_type_map->getJobTypeMap()) {
        job_generator_parameters[job_type_id] = new JobGeneratorParameters(
            job_type_id,
            // 200 za train, 500 za test
            100,
            new ExponentialDistribution(8),
            0,
            new UniformRealDistributionGenerator(0, 5)
            // job_type_id == 1 ? new UniformRealDistributionGenerator(0, 5) : new UniformRealDistributionGenerator(3, 8)
        );
    }

    auto generated_jobs = JobSequenceGenerator::generateJobs(
        job_generator_parameters,
        topology->getRootElement(),
        job_type_map,
        0,
        0
    );

    JobSequenceGeneratorSerializer::serializeJobs(dir + "job_sequence_test.yaml", generated_jobs);
}
