//
// Created by mihael on 5/27/24.
//

#ifndef LINEARGENETICPROGRAMMING_H
#define LINEARGENETICPROGRAMMING_H
#include "LGPProgram.h"
#include "LGPRegisterInitializationStrategy.h"
#include "OnlineSchedulingAlgorithm.h"


class LinearGeneticProgramming final : public OnlineSchedulingAlgorithm {
    LGPProgram* program;
    LGPRegisterInitializationStrategy* register_initialization_strategy;
    int number_of_registers;
public:
    LinearGeneticProgramming(LGPProgram* program, LGPRegisterInitializationStrategy* register_initialization_strategy, int number_of_registers);
    ~LinearGeneticProgramming() override;
    LGPProgram* getProgram();
    LGPRegisterInitializationStrategy* getRegisterInitializationStrategy();
    int getNumberOfRegisters();
    Genotype* copy() override;
    double calculateScore(std::map<std::string, double> params) override;
};



#endif //LINEARGENETICPROGRAMMING_H
