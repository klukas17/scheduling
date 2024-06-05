//
// Created by mihael on 6/3/24.
//

#ifndef HYPERPARAMETERTUNINGSERIALIZATIONOPERATOR_H
#define HYPERPARAMETERTUNINGSERIALIZATIONOPERATOR_H
#include "HyperparameterTuningGenotypeBlueprint.h"
#include "SerializationOperator.h"


class HyperparameterTuningSerializationOperator final : public SerializationOperator {
public:
    HyperparameterTuningGenotypeBlueprint* blueprint;
    explicit HyperparameterTuningSerializationOperator(HyperparameterTuningGenotypeBlueprint* blueprint);
    std::vector<std::string> serialize(Genotype* genotype) override;
    Genotype* deserialize(std::vector<std::string> representation) override;
};



#endif //HYPERPARAMETERTUNINGSERIALIZATIONOPERATOR_H
