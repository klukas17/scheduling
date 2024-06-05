//
// Created by mihael on 5/20/24.
//

#include "NeuralNetworkSerializationOperator.h"
#include "NeuralNetwork.h"
#include "sstream"

NeuralNetworkSerializationOperator::NeuralNetworkSerializationOperator(NeuralNetworkGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
}

NeuralNetworkSerializationOperator::~NeuralNetworkSerializationOperator() = default;

std::vector<std::string> NeuralNetworkSerializationOperator::serialize(Genotype* genotype) {
    auto neural_network = dynamic_cast<NeuralNetwork*>(genotype);
    auto matrices = neural_network->getMatrices();
    std::ostringstream oss;

    std::vector<std::string> result;

    for (auto matrix : matrices) {
        auto rows = matrix.rows(), cols = matrix.cols();
        oss << rows << " " << cols;
        result.push_back(oss.str());
        oss.str("");

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                oss << matrix(i, j);
                if (j != cols - 1) {
                    oss << " ";
                }
            }
            result.push_back(oss.str());
            oss.str("");
        }
    }

    return result;
}

Genotype* NeuralNetworkSerializationOperator::deserialize(std::vector<std::string> representation) {
    std::vector<Eigen::MatrixXd> matrices;

    std::istringstream iss(representation[0]);

    int i = 0;
    while (i < representation.size()) {
        int rows, cols;
        iss.clear();
        iss.str(representation[i]);
        iss >> rows >> cols;

        Eigen::MatrixXd m(rows, cols);

        double x;
        for (int row = 0; row < rows; row++) {
            i++;
            iss.clear();
            iss.str(representation[i]);
            for (int col = 0; col < cols; col++) {
                iss >> x;
                m(row, col) = x;
            }
        }

        matrices.push_back(m);
        i++;
    }

    return new NeuralNetwork(matrices, blueprint->activation_function_name);
}

