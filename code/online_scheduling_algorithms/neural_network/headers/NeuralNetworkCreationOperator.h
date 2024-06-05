//
// Created by mihael on 5/19/24.
//

#ifndef NEURALNETWORKCREATIONOPERATOR_H
#define NEURALNETWORKCREATIONOPERATOR_H
#include "CreationOperator.h"
#include "NeuralNetworkGenotypeBlueprint.h"


class NeuralNetworkCreationOperator final : public CreationOperator {
    NeuralNetworkGenotypeBlueprint* blueprint;
public:
    explicit NeuralNetworkCreationOperator(GenotypeBlueprint* genotype_blueprint);
    ~NeuralNetworkCreationOperator() override;
    Genotype* create() override;
};



#endif //NEURALNETWORKCREATIONOPERATOR_H
