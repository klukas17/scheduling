//
// Created by mihael on 5/31/24.
//

#ifndef STRUCTUREDGRAMMATICALEVOLUTIONCREATIONOPERATOR_H
#define STRUCTUREDGRAMMATICALEVOLUTIONCREATIONOPERATOR_H
#include "CreationOperator.h"
#include "StructuredGrammaticalEvolutionGenotypeBlueprint.h"


class StructuredGrammaticalEvolutionCreationOperator final : public CreationOperator {
    StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint;
public:
    explicit StructuredGrammaticalEvolutionCreationOperator(GenotypeBlueprint* blueprint);
    ~StructuredGrammaticalEvolutionCreationOperator() override;
    Genotype* create() override;
};



#endif //STRUCTUREDGRAMMATICALEVOLUTIONCREATIONOPERATOR_H
