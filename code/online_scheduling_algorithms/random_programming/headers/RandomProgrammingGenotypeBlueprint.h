//
// Created by mihael on 5/3/24.
//

#ifndef RANDOMPROGRAMMINGGENOTYPEBLUEPRINT_H
#define RANDOMPROGRAMMINGGENOTYPEBLUEPRINT_H

#include "GenotypeBlueprint.h"


class RandomProgrammingGenotypeBlueprint final : public GenotypeBlueprint {
public:
    double lower;
    double upper;
    RandomProgrammingGenotypeBlueprint(double lower, double upper);
};



#endif //RANDOMPROGRAMMINGGENOTYPEBLUEPRINT_H
