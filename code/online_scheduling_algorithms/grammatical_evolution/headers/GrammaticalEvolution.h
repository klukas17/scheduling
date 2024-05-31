//
// Created by mihael on 5/30/24.
//

#ifndef GRAMMATICALEVOLUTION_H
#define GRAMMATICALEVOLUTION_H
#include "GEProgram.h"
#include "OnlineSchedulingAlgorithm.h"


class GrammaticalEvolution final : public OnlineSchedulingAlgorithm {
    GEProgram* program;
public:
    explicit GrammaticalEvolution(GEProgram* program);
    ~GrammaticalEvolution() override;
    GEProgram* getProgram();
    Genotype* copy() override;
    double calculateScore(std::map<std::string, double> params) override;
};



#endif //GRAMMATICALEVOLUTION_H
