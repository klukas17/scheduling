//
// Created by mihael on 5/3/24.
//

#ifndef RANDOMPROGRAMMINGCOMBINATIONOPERATOR_H
#define RANDOMPROGRAMMINGCOMBINATIONOPERATOR_H

#include "CombinationOperator.h"


class RandomProgrammingCombinationOperator final : public CombinationOperator {
public:
    RandomProgrammingCombinationOperator();
    ~RandomProgrammingCombinationOperator() override;
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //RANDOMPROGRAMMINGCOMBINATIONOPERATOR_H
