//
// Created by mihael on 5/20/24.
//

#ifndef ONLINESCHEDULINGALGORITHMCLUSTERSERIALIZATIONOPERATOR_H
#define ONLINESCHEDULINGALGORITHMCLUSTERSERIALIZATIONOPERATOR_H
#include "SerializationOperator.h"
#include "Topology.h"


class OnlineSchedulingAlgorithmClusterSerializationOperator final : public SerializationOperator {
    Topology* topology;
    SerializationOperator* algorithm_serialization_operator;
public:
    OnlineSchedulingAlgorithmClusterSerializationOperator(Topology* topology, SerializationOperator* algorithm_serialization_operator);
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
};



#endif //ONLINESCHEDULINGALGORITHMCLUSTERSERIALIZATIONOPERATOR_H
