//
// Created by mihael on 5/8/24.
//

#ifndef CONSTANTPROGRAMMINGPERTURBATIONOPERATOR_H
#define CONSTANTPROGRAMMINGPERTURBATIONOPERATOR_H
#include "PerturbationOperator.h"


class ConstantProgrammingPerturbationOperator final : public PerturbationOperator {
public:
    ConstantProgrammingPerturbationOperator();
    void perturbate(Genotype* genotype) override;
};



#endif //CONSTANTPROGRAMMINGPERTURBATIONOPERATOR_H
