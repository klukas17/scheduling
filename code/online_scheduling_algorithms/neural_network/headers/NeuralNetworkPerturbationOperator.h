//
// Created by mihael on 5/19/24.
//

#ifndef NEURALNETWORKPERTURBATIONOPERATOR_H
#define NEURALNETWORKPERTURBATIONOPERATOR_H
#include "DoubleGenerator.h"
#include "PerturbationOperator.h"


class NeuralNetworkPerturbationOperator final : public PerturbationOperator {
    DoubleGenerator* delta_generator;
public:
    explicit NeuralNetworkPerturbationOperator(DoubleGenerator* delta_generator);
    void perturbate(Genotype* genotype) override;
};



#endif //NEURALNETWORKPERTURBATIONOPERATOR_H
