//
// Created by mihael on 5/3/24.
//

#ifndef RANDOMPROGRAMMINGPERTURBATIONOPERATOR_H
#define RANDOMPROGRAMMINGPERTURBATIONOPERATOR_H

#include "PerturbationOperator.h"


class RandomProgrammingPerturbationOperator final : public PerturbationOperator {
public:
    RandomProgrammingPerturbationOperator();
    ~RandomProgrammingPerturbationOperator() override;
    void perturbate(Genotype* genotype) override;
};



#endif //RANDOMPROGRAMMINGPERTURBATIONOPERATOR_H
