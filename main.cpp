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

std::string dir = "../examples/example_07/";

int main() {

    std::map<long, MachineType*> machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");

    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);

    std::map<long, JobType*> job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");

    std::map<long, Job*> jobs = JobSequenceParser::parse(dir + "job_sequence.yaml", job_type_map);

    Individual* individual = GenotypeDeserializer::deserialize(dir + "individual_1.yaml", topology);

    GenotypeSerializer::serialize(dir + "individual_1_copy.yaml", individual);

    Simulator::simulate(individual, jobs, true, dir + "simulator_logs.txt");

    return 0;
}