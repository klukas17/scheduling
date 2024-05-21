//
// Created by mihael on 5/19/24.
//

#ifndef NORMALDISTRIBUTION_H
#define NORMALDISTRIBUTION_H

#include <random>

#include "DoubleGenerator.h"

class NormalDistribution final : public DoubleGenerator {
    std::normal_distribution<> generator;
public:
    NormalDistribution(double mu, double sigma);
    double generate() override;
};



#endif //NORMALDISTRIBUTION_H
