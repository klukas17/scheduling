//
// Created by mihael on 5/19/24.
//

#ifndef NEURALNETWORKGENOTYPEBLUEPRINT_H
#define NEURALNETWORKGENOTYPEBLUEPRINT_H
#include <vector>

#include "DoubleGenerator.h"
#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"


class NeuralNetworkGenotypeBlueprint final : public OnlineSchedulingAlgorithmGenotypeBlueprint {
public:
    DoubleGenerator* double_generator;
    std::vector<int> layer_sizes;
    std::string activation_function_name;
    NeuralNetworkGenotypeBlueprint(DoubleGenerator* double_generator, std::vector<int> layer_sizes, std::string activation_function_name);
    ~NeuralNetworkGenotypeBlueprint() override;
};



#endif //NEURALNETWORKGENOTYPEBLUEPRINT_H
