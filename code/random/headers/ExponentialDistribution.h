//
// Created by mihael on 4/5/24.
//

#ifndef EXPONENTIALDISTRIBUTION_H
#define EXPONENTIALDISTRIBUTION_H
#include <random>

class ExponentialDistribution {
    std::exponential_distribution<> generator;
public:
    explicit ExponentialDistribution(double lambda);
    double generate();
};



#endif //EXPONENTIALDISTRIBUTION_H
