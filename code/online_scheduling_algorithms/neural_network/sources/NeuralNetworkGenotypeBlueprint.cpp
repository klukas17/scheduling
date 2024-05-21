//
// Created by mihael on 5/19/24.
//

#include "NeuralNetworkGenotypeBlueprint.h"

NeuralNetworkGenotypeBlueprint::NeuralNetworkGenotypeBlueprint(DoubleGenerator* double_generator, std::vector<int> layer_sizes) {
    this->double_generator = double_generator;
    this->layer_sizes = layer_sizes;
}
