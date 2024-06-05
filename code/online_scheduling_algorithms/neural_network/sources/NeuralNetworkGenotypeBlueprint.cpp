//
// Created by mihael on 5/19/24.
//

#include "NeuralNetworkGenotypeBlueprint.h"

#include <utility>

NeuralNetworkGenotypeBlueprint::NeuralNetworkGenotypeBlueprint(DoubleGenerator* double_generator, std::vector<int> layer_sizes, std::string activation_function_name) {
    this->double_generator = double_generator;
    this->layer_sizes = std::move(layer_sizes);
    this->activation_function_name = std::move(activation_function_name);
}

NeuralNetworkGenotypeBlueprint::~NeuralNetworkGenotypeBlueprint() {
    delete double_generator;
}
