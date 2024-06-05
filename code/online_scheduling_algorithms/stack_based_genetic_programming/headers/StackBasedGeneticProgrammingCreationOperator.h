//
// Created by mihael on 5/29/24.
//

#ifndef STACKBASEDGENETICPROGRAMMINGCREATIONOPERATOR_H
#define STACKBASEDGENETICPROGRAMMINGCREATIONOPERATOR_H
#include <vector>

#include "CreationOperator.h"
#include "DoubleGenerator.h"
#include "SBGPInstructionTypes.h"
#include "StackBasedGeneticProgrammingGenotypeBlueprint.h"


class StackBasedGeneticProgrammingCreationOperator final : public CreationOperator {
    StackBasedGeneticProgrammingGenotypeBlueprint* blueprint;
    std::vector<SBGPInstructionType> instructions;
    std::vector<double> instructions_probabilites;
    DoubleGenerator* instruction_type_generator;
    SBGPInstructionType generateInstructionType();
public:
    explicit StackBasedGeneticProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint);
    ~StackBasedGeneticProgrammingCreationOperator() override;
    Genotype* create() override;
};



#endif //STACKBASEDGENETICPROGRAMMINGCREATIONOPERATOR_H
