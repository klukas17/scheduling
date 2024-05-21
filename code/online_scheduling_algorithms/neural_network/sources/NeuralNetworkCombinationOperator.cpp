//
// Created by mihael on 5/19/24.
//

#include "NeuralNetworkCombinationOperator.h"

#include "NeuralNetwork.h"

NeuralNetworkCombinationOperator::NeuralNetworkCombinationOperator() = default;

Genotype* NeuralNetworkCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    auto nn_1 = dynamic_cast<NeuralNetwork*>(genotype1);
    auto nn_2 = dynamic_cast<NeuralNetwork*>(genotype2);

    auto matrices_1 = nn_1->getMatrices();
    auto matrices_2 = nn_2->getMatrices();

    std::vector<Eigen::MatrixXd> matrices;

    for (int i = 0; i < matrices_1.size(); i++) {
        matrices.push_back((matrices_1[i] + matrices_2[i]) / 2);
    }

    return new NeuralNetwork(matrices);
}
