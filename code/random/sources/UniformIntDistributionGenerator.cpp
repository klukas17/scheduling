//
// Created by mihael on 4/3/24.
//

#include "UniformIntDistributionGenerator.h"

UniformIntDistributionGenerator::UniformIntDistributionGenerator(int lower_limit, int upper_limit) {
    this->generator = std::uniform_int_distribution<int>(lower_limit, upper_limit);
}

int UniformIntDistributionGenerator::generate() {
    return this->generator(RandomnessEngine::getEngine());
}
