//
// Created by mihael on 5/29/24.
//

#ifndef STACKBASEDGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
#define STACKBASEDGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
#include "DoubleGenerator.h"
#include "IntegerGenerator.h"
#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"


class StackBasedGeneticProgrammingGenotypeBlueprint final : public OnlineSchedulingAlgorithmGenotypeBlueprint {
public:
    int number_of_instructions;
    double initialization_chance_of_nop;
    double push_constant_share;
    double push_param_share;
    DoubleGenerator* constant_generator;
    IntegerGenerator* generator;
    StackBasedGeneticProgrammingGenotypeBlueprint(
        int number_of_instructions,
        double initialization_chance_of_nop,
        double push_constant_share,
        double push_param_share,
        double constant_min,
        double constant_max
    );
    double generateConstant();
    std::string generateParam(std::vector<std::string> params);
};



#endif //STACKBASEDGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
