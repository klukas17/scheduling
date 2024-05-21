//
// Created by mihael on 5/19/24.
//

#include "NeuralNetworkCreationOperator.h"
#include "NeuralNetwork.h"

NeuralNetworkCreationOperator::NeuralNetworkCreationOperator(GenotypeBlueprint* genotype_blueprint) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<NeuralNetworkGenotypeBlueprint*>(genotype_blueprint);
}

Genotype* NeuralNetworkCreationOperator::create() {
    std::vector<Eigen::MatrixXd> matrices;

    auto inputs = blueprint->getInputs();

    auto layer_sizes = blueprint->layer_sizes;
    auto double_generator = blueprint->double_generator;

    std::vector<int> layers;
    layers.push_back(inputs.size());
    for (auto l : layer_sizes) {
        layers.push_back(l);
    }

    for (int k = 0; k < layers.size() - 1; k++) {
        auto rows = layers[k];
        auto cols = layers[k + 1];

        Eigen::MatrixXd m(rows + 1, cols + 1);

        for (int i = 0; i < rows; i++)
            m(i, cols) = 0;
        m(rows, cols) = 1;

        for (int i = 0; i <= rows; i++) {
            for (int j = 0; j < cols; j++) {
                m(i, j) = double_generator->generate();
            }
        }

        matrices.push_back(m);
    }

    return new NeuralNetwork(matrices);
}