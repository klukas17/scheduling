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
#include "filesystem"

void run_example(const std::string& dir) {
    std::map<long, MachineType*> machine_type_map = MachineSpecificationsParser::parse(dir + "machine_specifications.yaml");
    Topology* topology = MachineTopologyParser::parse(dir + "machine_topology.yaml", machine_type_map);
    std::map<long, JobType*> job_type_map = JobSpecificationsParser::parse(dir + "job_specifications.yaml");
    std::map<long, Job*> jobs = JobSequenceParser::parse(dir + "job_sequence.yaml", job_type_map);
    Individual* individual = GenotypeDeserializer::deserialize(dir + "individual.yaml", topology);
    GenotypeSerializer::serialize(dir + "individual_copy.yaml", individual);
    Simulator::simulate(individual, jobs, true, dir + "simulator_logs.txt");
}

int main() {
    for (const auto& entry : std::filesystem::directory_iterator("../examples/")) {
        if (entry.is_directory()) {
            run_example(entry.path().string() + "/");
        }
    }
}