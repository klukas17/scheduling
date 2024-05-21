//
// Created by mihael on 5/20/24.
//

#ifndef NEURALNETWORKSERIALIZATIONOPERATOR_H
#define NEURALNETWORKSERIALIZATIONOPERATOR_H
#include "SerializationOperator.h"


class NeuralNetworkSerializationOperator final : public SerializationOperator {
public:
    NeuralNetworkSerializationOperator();
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
};



#endif //NEURALNETWORKSERIALIZATIONOPERATOR_H
