//
// Created by mihael on 4/3/24.
//

#ifndef UNIFORMINTDISTRIBUTION_H
#define UNIFORMINTDISTRIBUTION_H
#include "IntegerGenerator.h"
#include "RandomnessEngine.h"


class UniformIntDistributionGenerator final: public IntegerGenerator {
    std::uniform_int_distribution<> generator;
public:
    UniformIntDistributionGenerator(int lower_limit, int upper_limit);
    int generate() override;
};



#endif //UNIFORMINTDISTRIBUTION_H
