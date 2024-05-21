//
// Created by mihael on 5/20/24.
//

#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"

#include <utility>

OnlineSchedulingAlgorithmGenotypeBlueprint::OnlineSchedulingAlgorithmGenotypeBlueprint() = default;

std::vector<std::string> OnlineSchedulingAlgorithmGenotypeBlueprint::getInputs() {
    return inputs;
}

void OnlineSchedulingAlgorithmGenotypeBlueprint::setInputs(std::vector<std::string> inputs) {
    this->inputs = std::move(inputs);
}

