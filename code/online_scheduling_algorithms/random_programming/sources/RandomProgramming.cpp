//
// Created by mihael on 5/3/24.
//

#include "RandomProgramming.h"

#include "UniformRealDistributionGenerator.h"

RandomProgramming::RandomProgramming(double lower, double upper) {
    this->lower = lower;
    this->upper = upper;
    this->generator = new UniformRealDistributionGenerator(lower, upper);
}

Genotype* RandomProgramming::copy() {
    return new RandomProgramming(lower, upper);
}

double RandomProgramming::calculateScore(std::map<std::string, double> params) {
    return this->generator->generate();
}
