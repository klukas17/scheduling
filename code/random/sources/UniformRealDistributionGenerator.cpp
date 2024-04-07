//
// Created by mihael on 4/4/24.
//

#include "UniformRealDistributionGenerator.h"

#include "RandomnessEngine.h"

UniformRealDistributionGenerator::UniformRealDistributionGenerator(double const lower_limit, double const upper_limit) {
    this->generator = std::uniform_real_distribution(lower_limit, upper_limit);
}

double UniformRealDistributionGenerator::generate() {
    return this->generator(RandomnessEngine::getEngine());
}

