//
// Created by mihael on 4/5/24.
//

#ifndef EXPONENTIALDISTRIBUTION_H
#define EXPONENTIALDISTRIBUTION_H
#include <random>

#include "DoubleGenerator.h"

class ExponentialDistribution final : public DoubleGenerator {
    std::exponential_distribution<> generator;
public:
    explicit ExponentialDistribution(double lambda);
    double generate() override;
};



#endif //EXPONENTIALDISTRIBUTION_H
