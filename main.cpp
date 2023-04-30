#include <iostream>
#include "MachineSpecificationsParser.h"
#include "MachineTopologyParser.h"
#include "JobSpecificationsParser.h"
#include "JobSequenceParser.h"
#include "GenotypeDeserializer.h"
#include "GenotypeSerializer.h"
#include "Simulator.h"
#include "MachineType.h"
#include "Topology.h"
#include "Individual.h"

std::string dir = "../examples/example_01/";

int main() {
    std::cout << "Hello, World!" << std::endl;

    MachineSpecificationsParser* machine_specifications_parser = new MachineSpecificationsParser();
    std::map<long, MachineType*> machine_type_map = machine_specifications_parser->parse(dir + "machine_specifications.yaml");

    MachineTopologyParser* machine_topology_parser = new MachineTopologyParser();
    Topology* topology = machine_topology_parser->parse(dir + "machine_topology.yaml", machine_type_map);

    JobSpecificationsParser* job_specifications_parser = new JobSpecificationsParser();
    std::map<long, JobType*> job_type_map = job_specifications_parser->parse(dir + "job_specifications.yaml");

    JobSequenceParser* job_sequence_parser = new JobSequenceParser();
    std::vector<Job*> jobs = job_sequence_parser->parse(dir + "job_sequence.yaml", job_type_map);

    GenotypeDeserializer* genotype_deserializer = new GenotypeDeserializer(topology);
    Individual* individual = genotype_deserializer->deserialize(dir + "individual_1.yaml");

    GenotypeSerializer* genotype_serializer = new GenotypeSerializer();
    genotype_serializer->serialize(dir + "individual_1_copy.yaml", individual);

    Simulator* simulator = new Simulator();
    simulator->simulate(individual, jobs, dir + "simulator_logs.txt");

    return 0;
}