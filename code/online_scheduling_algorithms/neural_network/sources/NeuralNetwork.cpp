//
// Created by mihael on 5/19/24.
//

#include "NeuralNetwork.h"

#include <iostream>
#include <utility>

NeuralNetwork::NeuralNetwork(std::vector<Eigen::MatrixXd> matrices) {
    this->matrices = std::move(matrices);
}

NeuralNetwork::~NeuralNetwork() = default;

std::vector<Eigen::MatrixXd> NeuralNetwork::getMatrices() {
    return matrices;
}

void NeuralNetwork::setMatrices(std::vector<Eigen::MatrixXd> matrices) {
    this->matrices = std::move(matrices);
}

Genotype* NeuralNetwork::copy() {
    std::vector<Eigen::MatrixXd> matrices_copy;
    for (auto const m : matrices) {
        Eigen::MatrixXd n = m;
        matrices_copy.push_back(n);
    }
    return new NeuralNetwork(matrices_copy);
}

double sigm(double x) {
    return 1 / (1 + exp(-x));
}

double relu(double x) {
    return std::max(0., x);
}

double NeuralNetwork::calculateScore(std::map<std::string, double> params) {
    Eigen::MatrixXd v(1, inputs.size() + 1);

    for (int i = 0; i < inputs.size(); i++) {
        v(0, i) = params[inputs[i]];
    }
    v(0, inputs.size()) = 1;

    for (int i = 0; i < matrices.size(); i++) {
        v = v * matrices[i];
        if (i != matrices.size() - 1) {
            v = v.unaryExpr(&relu);
            v(0, v.cols() - 1) = 1;
        }
    }

    return v(0, 0);
}
