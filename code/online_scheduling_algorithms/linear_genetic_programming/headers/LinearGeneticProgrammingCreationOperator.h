//
// Created by mihael on 5/27/24.
//

#ifndef LINEARGENETICPROGRAMMINGCREATIONOPERATOR_H
#define LINEARGENETICPROGRAMMINGCREATIONOPERATOR_H
#include "CreationOperator.h"
#include "LGPInstructionTypes.h"
#include "LinearGeneticProgrammingGenotypeBlueprint.h"


class LinearGeneticProgrammingCreationOperator final : public CreationOperator {
    LinearGeneticProgrammingGenotypeBlueprint* blueprint;
    std::vector<LGPInstructionType> instructions;
    std::vector<double> instructions_probabilites;
    DoubleGenerator* instruction_type_generator;
    LGPInstructionType generateInstructionType();
public:
    explicit LinearGeneticProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint);
    Genotype* create() override;
};



#endif //LINEARGENETICPROGRAMMINGCREATIONOPERATOR_H
