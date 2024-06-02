//
// Created by mihael on 6/1/24.
//

#ifndef GRAPHBASEDGENETICPROGRAMMING_H
#define GRAPHBASEDGENETICPROGRAMMING_H
#include "GBGPProgram.h"
#include "OnlineSchedulingAlgorithm.h"


class GraphBasedGeneticProgramming final : public OnlineSchedulingAlgorithm {
    GBGPProgram* program;
public:
    GraphBasedGeneticProgramming(GBGPProgram* program);
    ~GraphBasedGeneticProgramming() override;
    GBGPProgram* getProgram();
    Genotype* copy() override;
    double calculateScore(std::map<std::string, double> params) override;
};



#endif //GRAPHBASEDGENETICPROGRAMMING_H
