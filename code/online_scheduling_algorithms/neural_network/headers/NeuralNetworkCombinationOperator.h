//
// Created by mihael on 5/19/24.
//

#ifndef NEURALNETWORKCOMBINATIONOPERATOR_H
#define NEURALNETWORKCOMBINATIONOPERATOR_H
#include "CombinationOperator.h"


class NeuralNetworkCombinationOperator final : public CombinationOperator {
public:
    NeuralNetworkCombinationOperator();
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //NEURALNETWORKCOMBINATIONOPERATOR_H
