//
// Created by mihael on 5/3/24.
//

#ifndef RANDOMPROGRAMMINGCREATIONOPERATOR_H
#define RANDOMPROGRAMMINGCREATIONOPERATOR_H

#include "CreationOperator.h"
#include "RandomProgrammingGenotypeBlueprint.h"


class RandomProgrammingCreationOperator final : public CreationOperator {
    RandomProgrammingGenotypeBlueprint* blueprint;
public:
    explicit RandomProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint);
    ~RandomProgrammingCreationOperator() override;
    Genotype* create() override;
};



#endif //RANDOMPROGRAMMINGCREATIONOPERATOR_H
