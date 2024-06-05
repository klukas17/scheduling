//
// Created by mihael on 5/30/24.
//

#ifndef MULTIEXPRESSIONPROGRAMMINGCREATIONOPERATOR_H
#define MULTIEXPRESSIONPROGRAMMINGCREATIONOPERATOR_H
#include "CreationOperator.h"
#include "MultiExpressionProgrammingGenotypeBlueprint.h"


class MultiExpressionProgrammingCreationOperator final : public CreationOperator {
    MultiExpressionProgrammingGenotypeBlueprint* blueprint;
public:
    explicit MultiExpressionProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint);
    ~MultiExpressionProgrammingCreationOperator() override;
    Genotype* create() override;
};



#endif //MULTIEXPRESSIONPROGRAMMINGCREATIONOPERATOR_H
