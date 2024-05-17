//
// Created by mihael on 5/8/24.
//

#ifndef CONSTANTPROGRAMMINGCREATIONOPERATOR_H
#define CONSTANTPROGRAMMINGCREATIONOPERATOR_H
#include "ConstantProgrammingGenotypeBlueprint.h"
#include "CreationOperator.h"


class ConstantProgrammingCreationOperator final : public CreationOperator {
    ConstantProgrammingGenotypeBlueprint* blueprint;
public:
    ConstantProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint);
    Genotype* create() override;
};



#endif //CONSTANTPROGRAMMINGCREATIONOPERATOR_H
