//
// Created by mihael on 5/23/24.
//

#ifndef CARTESIANGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
#define CARTESIANGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
#include "CGPFunctionsIndex.h"
#include "DoubleGenerator.h"
#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"


class CartesianGeneticProgrammingGenotypeBlueprint final : public OnlineSchedulingAlgorithmGenotypeBlueprint {
public:
    int rows;
    int cols;
    CGPFunctionsIndex* functions_index;
    DoubleGenerator* constant_generator;
    CartesianGeneticProgrammingGenotypeBlueprint(int rows, int cols, CGPFunctionsIndex* functions_index, double constant_min, double constant_max);
    double generateConstant();
};



#endif //CARTESIANGENETICPROGRAMMINGGENOTYPEBLUEPRINT_H
