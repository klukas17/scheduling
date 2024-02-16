//
// Created by mihael on 2/16/24.
//

#ifndef PERTURBATIONOPERATOR_H
#define PERTURBATIONOPERATOR_H
#include "Genotype.h"


class PerturbationOperator {
public:
    virtual void perturbate(Genotype* genotype) = 0;
    virtual ~PerturbationOperator() = 0;
};



#endif //PERTURBATIONOPERATOR_H
