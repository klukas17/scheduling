//
// Created by mihael on 5/27/24.
//

#ifndef LINEARGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
#define LINEARGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
#include "LGPInstructionTypes.h"
#include "LinearGeneticProgrammingGenotypeBlueprint.h"
#include "PerturbationOperator.h"


class LinearGeneticProgrammingPerturbationOperator final : public PerturbationOperator {
    LinearGeneticProgrammingGenotypeBlueprint* blueprint;
    std::vector<LGPInstructionType> instructions;
    std::vector<double> instructions_probabilites;
    DoubleGenerator* instruction_type_generator;
    IntegerGenerator* generator;
    double perturbation_rate;
    LGPInstructionType generateInstructionType();
public:
    LinearGeneticProgrammingPerturbationOperator(LinearGeneticProgrammingGenotypeBlueprint* blueprint, double perturbation_rate, double perturbation_chance_of_nop);
    ~LinearGeneticProgrammingPerturbationOperator() override;
    void perturbate(Genotype* genotype) override;
};



#endif //LINEARGENETICPROGRAMMINGPERTURBATIONOPERATOR_H
