//
// Created by mihael on 2/16/24.
//

#ifndef COMBINATIONOPERATOR_H
#define COMBINATIONOPERATOR_H

#include "Genotype.h"

class CombinationOperator {
public:
    virtual Genotype* combine(Genotype* genotype1, Genotype* genotype2) = 0;
    virtual ~CombinationOperator() = 0;
};



#endif //COMBINATIONOPERATOR_H
