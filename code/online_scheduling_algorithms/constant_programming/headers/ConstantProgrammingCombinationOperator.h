//
// Created by mihael on 5/8/24.
//

#ifndef CONSTANTPROGRAMMINGCOMBINATIONOPERATOR_H
#define CONSTANTPROGRAMMINGCOMBINATIONOPERATOR_H
#include "CombinationOperator.h"


class ConstantProgrammingCombinationOperator final : public CombinationOperator {
public:
    ConstantProgrammingCombinationOperator();
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //CONSTANTPROGRAMMINGCOMBINATIONOPERATOR_H
