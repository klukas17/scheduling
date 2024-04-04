//
// Created by mihael on 4/3/24.
//

#ifndef UNIFORMINTDISTRIBUTION_H
#define UNIFORMINTDISTRIBUTION_H
#include "RandomnessEngine.h"


class UniformIntDistributionGenerator {
private:
    std::uniform_int_distribution<int> generator;
public:
    UniformIntDistributionGenerator(int lower_limit, int upper_limit);
    int generate();
};



#endif //UNIFORMINTDISTRIBUTION_H
