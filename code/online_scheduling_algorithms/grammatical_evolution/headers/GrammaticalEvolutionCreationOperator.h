//
// Created by mihael on 5/30/24.
//

#ifndef GRAMMATICALEVOLUTIONCREATIONOPERATOR_H
#define GRAMMATICALEVOLUTIONCREATIONOPERATOR_H
#include "CreationOperator.h"
#include "GrammaticalEvolutionGenotypeBlueprint.h"


class GrammaticalEvolutionCreationOperator final : public CreationOperator {
    GrammaticalEvolutionGenotypeBlueprint* blueprint;
public:
    explicit GrammaticalEvolutionCreationOperator(GenotypeBlueprint* genotype_blueprint);
    Genotype* create() override;
};



#endif //GRAMMATICALEVOLUTIONCREATIONOPERATOR_H
