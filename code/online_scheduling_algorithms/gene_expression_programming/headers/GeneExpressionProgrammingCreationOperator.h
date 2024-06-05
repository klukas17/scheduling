//
// Created by mihael on 5/29/24.
//

#ifndef GENEEXPRESSIONPROGRAMMINGCREATIONOPERATOR_H
#define GENEEXPRESSIONPROGRAMMINGCREATIONOPERATOR_H
#include "CreationOperator.h"
#include "GeneExpressionProgrammingGenotypeBlueprint.h"


class GeneExpressionProgrammingCreationOperator final : public CreationOperator {
    GeneExpressionProgrammingGenotypeBlueprint* blueprint;
public:
    explicit GeneExpressionProgrammingCreationOperator(GenotypeBlueprint* blueprint);
    ~GeneExpressionProgrammingCreationOperator() override;
    Genotype* create() override;
};



#endif //GENEEXPRESSIONPROGRAMMINGCREATIONOPERATOR_H
