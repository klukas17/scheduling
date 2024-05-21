//
// Created by mihael on 5/20/24.
//

#include "OnlineSchedulingAlgorithmClusterSerializationOperator.h"
#include "OnlineSchedulingAlgorithm.h"
#include "OnlineSchedulingAlgorithmCluster.h"
#include "sstream"

OnlineSchedulingAlgorithmClusterSerializationOperator::OnlineSchedulingAlgorithmClusterSerializationOperator(Topology* topology, SerializationOperator* algorithm_serialization_operator) {
    this->topology = topology;
    this->algorithm_serialization_operator = algorithm_serialization_operator;
}

std::vector<std::string> OnlineSchedulingAlgorithmClusterSerializationOperator::serialize(Genotype* genotype) {
    auto cluster = dynamic_cast<OnlineSchedulingAlgorithmCluster*>(genotype);

    std::ostringstream oss;

    std::vector<std::string> result;

    for (auto [machine_id, algorithm] : cluster->getAlgorithms()) {
        oss << "machine " << machine_id;
        result.push_back(oss.str());
        oss.str("");
        auto algorithm_serialized = algorithm_serialization_operator->serialize(algorithm);
        for (const auto& line : algorithm_serialized) {
            result.push_back(line);
        }
    }

    return result;
}

Genotype* OnlineSchedulingAlgorithmClusterSerializationOperator::deserialize(std::vector<std::string> representation) {
    std::map<long, OnlineSchedulingAlgorithm*> algorithms;

    std::istringstream iss(representation[0]);

    int i = 0;
    while (i < representation.size()) {
        iss.clear();
        iss.str(representation[i]);
        std::string _;
        long machine_id;
        iss >> _ >> machine_id;

        std::vector<std::string> lines;

        i++;
        while (i < representation.size() && !representation[i].starts_with("machine")) {
            lines.push_back(representation[i]);
            i++;
        }

        auto algorithm = algorithm_serialization_operator->deserialize(lines);
        algorithms[machine_id] = dynamic_cast<OnlineSchedulingAlgorithm*>(algorithm);
    }

    return new OnlineSchedulingAlgorithmCluster(topology, algorithms);
}
