//
// Created by mihael on 5/29/24.
//

#ifndef GENEEXPRESSIONPROGRAMMING_H
#define GENEEXPRESSIONPROGRAMMING_H
#include "GEPProgram.h"
#include "OnlineSchedulingAlgorithm.h"


class GeneExpressionProgramming final : public OnlineSchedulingAlgorithm {
    GEPProgram* program;
public:
    explicit GeneExpressionProgramming(GEPProgram* program);
    ~GeneExpressionProgramming() override;
    GEPProgram* getProgram();
    Genotype* copy() override;
    double calculateScore(std::map<std::string, double> params) override;
};



#endif //GENEEXPRESSIONPROGRAMMING_H
