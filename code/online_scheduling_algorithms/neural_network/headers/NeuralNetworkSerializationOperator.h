//
// Created by mihael on 5/20/24.
//

#ifndef NEURALNETWORKSERIALIZATIONOPERATOR_H
#define NEURALNETWORKSERIALIZATIONOPERATOR_H
#include "NeuralNetworkGenotypeBlueprint.h"
#include "SerializationOperator.h"


class NeuralNetworkSerializationOperator final : public SerializationOperator {
    NeuralNetworkGenotypeBlueprint* blueprint;
public:
    explicit NeuralNetworkSerializationOperator(NeuralNetworkGenotypeBlueprint* blueprint);
    ~NeuralNetworkSerializationOperator() override;
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
};



#endif //NEURALNETWORKSERIALIZATIONOPERATOR_H
