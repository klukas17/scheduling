//
// Created by mihael on 5/3/24.
//

#ifndef RANDOMPROGRAMMING_H
#define RANDOMPROGRAMMING_H

#include <map>
#include <string>
#include "DoubleGenerator.h"
#include "OnlineSchedulingAlgorithm.h"


class RandomProgramming final : public OnlineSchedulingAlgorithm {
    double lower;
    double upper;
    DoubleGenerator* generator;
public:
    RandomProgramming(double lower, double upper);
    double getLower();
    double getUpper();
    ~RandomProgramming();
    Genotype* copy() override;
    double calculateScore(std::map<std::string, double> params) override;
};



#endif //RANDOMPROGRAMMING_H
