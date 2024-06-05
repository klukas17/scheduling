//
// Created by mihael on 5/19/24.
//

#include "NeuralNetworkPerturbationOperator.h"

#include "NeuralNetwork.h"

NeuralNetworkPerturbationOperator::NeuralNetworkPerturbationOperator(DoubleGenerator* delta_generator) {
    this->delta_generator = delta_generator;
}

NeuralNetworkPerturbationOperator::~NeuralNetworkPerturbationOperator() {
    delete delta_generator;
}


void NeuralNetworkPerturbationOperator::perturbate(Genotype* genotype) {
    auto nn = dynamic_cast<NeuralNetwork*>(genotype);
    auto matrices = nn->getMatrices();

    for (int i = 0; i < matrices.size(); i++) {
        for (int j = 0; j < matrices[i].rows(); j++) {
            for (int k = 0; k < matrices[i].cols() - 1; k++) {
                matrices[i](j, k) = matrices[i](j, k) + delta_generator->generate();
            }
        }
    }

    nn->setMatrices(matrices);
}

