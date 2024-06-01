//
// Created by mihael on 5/31/24.
//

#ifndef STRUCTUREDGRAMMATICALEVOLUTION_H
#define STRUCTUREDGRAMMATICALEVOLUTION_H
#include "OnlineSchedulingAlgorithm.h"
#include "SGEProgram.h"


class StructuredGrammaticalEvolution final : public OnlineSchedulingAlgorithm {
    SGEProgram* program;
public:
    explicit StructuredGrammaticalEvolution(SGEProgram* program);
    ~StructuredGrammaticalEvolution() override;
    SGEProgram* getProgram();
    Genotype* copy() override;
    double calculateScore(std::map<std::string, double> params) override;
};



#endif //STRUCTUREDGRAMMATICALEVOLUTION_H
