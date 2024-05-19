//
// Created by mihael on 5/8/24.
//

#ifndef CONSTANTPROGRAMMING_H
#define CONSTANTPROGRAMMING_H
#include "OnlineSchedulingAlgorithm.h"


class ConstantProgramming final : public OnlineSchedulingAlgorithm {
    double constant;
public:
    explicit ConstantProgramming(double constant);
    ~ConstantProgramming();
    Genotype* copy() override;
    double calculateScore(std::map<std::string, double> params) override;
};



#endif //CONSTANTPROGRAMMING_H
