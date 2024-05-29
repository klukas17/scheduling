//
// Created by mihael on 5/29/24.
//

#ifndef STACKBASEDGENETICPROGRAMMING_H
#define STACKBASEDGENETICPROGRAMMING_H
#include "OnlineSchedulingAlgorithm.h"
#include "SBGPProgram.h"


class StackBasedGeneticProgramming final : public OnlineSchedulingAlgorithm {
    SBGPProgram* program;
public:
    explicit StackBasedGeneticProgramming(SBGPProgram* program);
    ~StackBasedGeneticProgramming() override;
    SBGPProgram* getProgram();
    Genotype* copy() override;
    double calculateScore(std::map<std::string, double> params) override;
};



#endif //STACKBASEDGENETICPROGRAMMING_H
