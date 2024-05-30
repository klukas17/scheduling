//
// Created by mihael on 5/30/24.
//

#ifndef MULTIEXPRESSIONPROGRAMMINGPERTURBATIONOPERATOR_H
#define MULTIEXPRESSIONPROGRAMMINGPERTURBATIONOPERATOR_H
#include "MultiExpressionProgrammingGenotypeBlueprint.h"
#include "PerturbationOperator.h"


class MultiExpressionProgrammingPerturbationOperator final : public PerturbationOperator {
    MultiExpressionProgrammingGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
    double perturbation_rate;
public:
    MultiExpressionProgrammingPerturbationOperator(MultiExpressionProgrammingGenotypeBlueprint* blueprint, double perturbation_rate);
    void perturbate(Genotype* genotype) override;
};



#endif //MULTIEXPRESSIONPROGRAMMINGPERTURBATIONOPERATOR_H
