//
// Created by mihael on 4/5/24.
//

#include "ExponentialDistribution.h"

#include "RandomnessEngine.h"

ExponentialDistribution::ExponentialDistribution(double const lambda) {
    this->generator = std::exponential_distribution(lambda);
}

double ExponentialDistribution::generate() {
    return this->generator(RandomnessEngine::getEngine());
}

