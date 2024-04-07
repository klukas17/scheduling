//
// Created by mihael on 4/3/24.
//

#ifndef UNIFORMINTDISTRIBUTION_H
#define UNIFORMINTDISTRIBUTION_H
#include "RandomnessEngine.h"


class UniformIntDistributionGenerator {
    std::uniform_int_distribution<> generator;
public:
    UniformIntDistributionGenerator(int lower_limit, int upper_limit);
    int generate();
};



#endif //UNIFORMINTDISTRIBUTION_H
