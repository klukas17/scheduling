//
// Created by mihael on 5/27/24.
//

#ifndef LINEARGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
#define LINEARGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
#include "DoubleGenerator.h"
#include "IntegerGenerator.h"
#include "LGPRegisterInitializationStrategy.h"
#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"


class LinearGeneticProgrammingGenotypeBlueprint final : public OnlineSchedulingAlgorithmGenotypeBlueprint {
public:
    LGPRegisterInitializationStrategy* register_initialization_strategy;
    int number_of_registers;
    int number_of_instructions;
    double initialization_chance_of_nop;
    DoubleGenerator* constant_generator;
    IntegerGenerator* generator;
    LinearGeneticProgrammingGenotypeBlueprint(
        LGPRegisterInitializationStrategy* register_initialization_strategy,
        int number_of_registers,
        int number_of_instructions,
        double initialization_chance_of_nop,
        double constant_min,
        double constant_max
    );
    ~LinearGeneticProgrammingGenotypeBlueprint() override;
    double generateConstant();
    std::string generateParam(std::vector<std::string> params);
    int generateRegister();
};



#endif //LINEARGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
