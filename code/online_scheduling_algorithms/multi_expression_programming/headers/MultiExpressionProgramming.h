//
// Created by mihael on 5/30/24.
//

#ifndef MULTIEXPRESSIONPROGRAMMING_H
#define MULTIEXPRESSIONPROGRAMMING_H
#include "MEPProgram.h"
#include "OnlineSchedulingAlgorithm.h"


class MultiExpressionProgramming final : public OnlineSchedulingAlgorithm {
    MEPProgram* program;
public:
    explicit MultiExpressionProgramming(MEPProgram* program);
    ~MultiExpressionProgramming() override;
    MEPProgram* getProgram();
    Genotype* copy() override;
    double calculateScore(std::map<std::string, double> params) override;
};



#endif //MULTIEXPRESSIONPROGRAMMING_H
