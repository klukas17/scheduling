//
// Created by mihael on 5/23/24.
//

#ifndef CARTESIANGENETICPROGRAMMING_H
#define CARTESIANGENETICPROGRAMMING_H
#include "CGPGrid.h"
#include "OnlineSchedulingAlgorithm.h"


class CartesianGeneticProgramming final : public OnlineSchedulingAlgorithm {
    CGPGrid* grid;
public:
    explicit CartesianGeneticProgramming(CGPGrid* grid);
    ~CartesianGeneticProgramming() override;
    CGPGrid* getGrid();
    Genotype* copy() override;
    double calculateScore(std::map<std::string, double> params) override;
};



#endif //CARTESIANGENETICPROGRAMMING_H
