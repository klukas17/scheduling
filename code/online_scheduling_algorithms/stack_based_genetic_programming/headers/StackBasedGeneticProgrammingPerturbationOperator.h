//
// Created by mihael on 5/29/24.
//

#ifndef STACKBASEDGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
#define STACKBASEDGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
#include <vector>

#include "DoubleGenerator.h"
#include "IntegerGenerator.h"
#include "PerturbationOperator.h"
#include "SBGPInstructionTypes.h"
#include "StackBasedGeneticProgrammingGenotypeBlueprint.h"


class StackBasedGeneticProgrammingPerturbationOperator final : public PerturbationOperator {
    StackBasedGeneticProgrammingGenotypeBlueprint* blueprint;
    std::vector<SBGPInstructionType> instructions;
    std::vector<double> instructions_probabilites;
    DoubleGenerator* instruction_type_generator;
    IntegerGenerator* generator;
    double perturbation_rate;
    SBGPInstructionType generateInstructionType();
public:
    StackBasedGeneticProgrammingPerturbationOperator(StackBasedGeneticProgrammingGenotypeBlueprint* blueprint, double perturbation_rate, double perturbation_chance_of_nop);
    void perturbate(Genotype* genotype) override;
};



#endif //STACKBASEDGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
