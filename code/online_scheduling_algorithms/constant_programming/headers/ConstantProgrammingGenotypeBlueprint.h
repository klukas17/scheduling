//
// Created by mihael on 5/8/24.
//

#ifndef CONSTANTPROGRAMMINGGENOTYPEBLUEPRINT_H
#define CONSTANTPROGRAMMINGGENOTYPEBLUEPRINT_H

#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"


class ConstantProgrammingGenotypeBlueprint final : public OnlineSchedulingAlgorithmGenotypeBlueprint {
public:
    double constant;
    ConstantProgrammingGenotypeBlueprint(double constant);
};



#endif //CONSTANTPROGRAMMINGGENOTYPEBLUEPRINT_H
