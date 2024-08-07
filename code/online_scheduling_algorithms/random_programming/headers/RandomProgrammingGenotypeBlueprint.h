//
// Created by mihael on 5/3/24.
//

#ifndef RANDOMPROGRAMMINGGENOTYPEBLUEPRINT_H
#define RANDOMPROGRAMMINGGENOTYPEBLUEPRINT_H

#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"


class RandomProgrammingGenotypeBlueprint final : public OnlineSchedulingAlgorithmGenotypeBlueprint {
public:
    double lower;
    double upper;
    RandomProgrammingGenotypeBlueprint(double lower, double upper);
    ~RandomProgrammingGenotypeBlueprint() override;
};



#endif //RANDOMPROGRAMMINGGENOTYPEBLUEPRINT_H
