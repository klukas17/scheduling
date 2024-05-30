//
// Created by mihael on 5/30/24.
//

#ifndef MULTIEXPRESSIONPROGRAMMINGCOMBINATIONOPERATOR_H
#define MULTIEXPRESSIONPROGRAMMINGCOMBINATIONOPERATOR_H
#include "CombinationOperator.h"
#include "MultiExpressionProgrammingGenotypeBlueprint.h"


class MultiExpressionProgrammingCombinationOperator final : public CombinationOperator {
    MultiExpressionProgrammingGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
public:
    explicit MultiExpressionProgrammingCombinationOperator(MultiExpressionProgrammingGenotypeBlueprint* blueprint);
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //MULTIEXPRESSIONPROGRAMMINGCOMBINATIONOPERATOR_H
