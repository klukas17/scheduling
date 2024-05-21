//
// Created by mihael on 5/19/24.
//

#include "NormalDistribution.h"

#include "RandomnessEngine.h"

NormalDistribution::NormalDistribution(double mu, double sigma) {
    this->generator = std::normal_distribution(mu, sigma);
}

double NormalDistribution::generate() {
    return this->generator(RandomnessEngine::getEngine());
}

