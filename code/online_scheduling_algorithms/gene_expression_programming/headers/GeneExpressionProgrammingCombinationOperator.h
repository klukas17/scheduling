//
// Created by mihael on 5/29/24.
//

#ifndef GENEEXPRESSIONPROGRAMMINGCOMBINATIONOPERATOR_H
#define GENEEXPRESSIONPROGRAMMINGCOMBINATIONOPERATOR_H
#include "CombinationOperator.h"
#include "GeneExpressionProgrammingGenotypeBlueprint.h"


class GeneExpressionProgrammingCombinationOperator final : public CombinationOperator {
    GeneExpressionProgrammingGenotypeBlueprint* blueprint;
    IntegerGenerator* generator;
public:
    explicit GeneExpressionProgrammingCombinationOperator(GeneExpressionProgrammingGenotypeBlueprint* blueprint);
    Genotype* combine(Genotype* genotype1, Genotype* genotype2) override;
};



#endif //GENEEXPRESSIONPROGRAMMINGCOMBINATIONOPERATOR_H
