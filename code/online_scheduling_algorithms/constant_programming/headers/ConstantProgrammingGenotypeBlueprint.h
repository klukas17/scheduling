//
// Created by mihael on 5/8/24.
//

#ifndef CONSTANTPROGRAMMINGGENOTYPEBLUEPRINT_H
#define CONSTANTPROGRAMMINGGENOTYPEBLUEPRINT_H

#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"


class ConstantProgrammingGenotypeBlueprint final : public OnlineSchedulingAlgorithmGenotypeBlueprint {
public:
    double constant;
    explicit ConstantProgrammingGenotypeBlueprint(double constant);
    ~ConstantProgrammingGenotypeBlueprint() override;
};



#endif //CONSTANTPROGRAMMINGGENOTYPEBLUEPRINT_H
