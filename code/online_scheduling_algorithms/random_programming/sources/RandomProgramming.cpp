//
// Created by mihael on 5/3/24.
//

#include "RandomProgramming.h"

#include "UniformRealDistributionGenerator.h"

#include "iostream"

RandomProgramming::RandomProgramming(double lower, double upper) {
    this->lower = lower;
    this->upper = upper;
    this->generator = new UniformRealDistributionGenerator(lower, upper);
}

Genotype* RandomProgramming::copy() {
    return new RandomProgramming(lower, upper);
}

double RandomProgramming::calculateScore(std::map<std::string, double> params) {
    for (const auto& [param_name, param_value] : params) {
        std::cout << param_name << "=" << param_value << ", ";
    }
    std::cout << std::endl;
    return this->generator->generate();
}
