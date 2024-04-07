//
// Created by mihael on 4/4/24.
//

#ifndef UNIFORMREALDISTRIBUTIONGENERATOR_H
#define UNIFORMREALDISTRIBUTIONGENERATOR_H
#include <random>


class UniformRealDistributionGenerator {
    std::uniform_real_distribution<> generator;
public:
    UniformRealDistributionGenerator(double lower_limit, double upper_limit);
    double generate();
};



#endif //UNIFORMREALDISTRIBUTIONGENERATOR_H
