//
// Created by mihael on 5/19/24.
//

#include "NeuralNetwork.h"

#include <utility>
#include <cmath>

double sigm(double x) {
    return 1 / (1 + exp(-x));
}

double relu(double x) {
    return (x >= 0) * x;
}

double tanh(double x) {
    return std::sinh(x) / std::cosh(x);
}

double lrelu(double x) {
    return (x >= 0) * x + (x < 0) * 0.01 * x;
}

NeuralNetwork::NeuralNetwork(std::vector<Eigen::MatrixXd> matrices, const std::string& activation_function_name) {
    this->matrices = std::move(matrices);
    this->activation_function_name = activation_function_name;
    if (activation_function_name == "sigm") {
        this->activation_function = &sigm;
    } else if (activation_function_name == "relu") {
        this->activation_function = &relu;
    } else if (activation_function_name == "tanh") {
        this->activation_function = &tanh;
    } else if (activation_function_name == "lrelu") {
        this->activation_function = &lrelu;
    } else {
        throw std::invalid_argument("Unsupported activation function");
    }
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
    return new NeuralNetwork(matrices_copy, activation_function_name);
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
            v = v.unaryExpr(this->activation_function);
            v(0, v.cols() - 1) = 1;
        }
    }

    return v(0, 0);
}
