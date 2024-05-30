//
// Created by mihael on 5/29/24.
//

#ifndef GENEEXPRESSIONPROGRAMMINGPERTURBATIONOPERATOR_H
#define GENEEXPRESSIONPROGRAMMINGPERTURBATIONOPERATOR_H
#include "GeneExpressionProgrammingGenotypeBlueprint.h"
#include "PerturbationOperator.h"


class GeneExpressionProgrammingPerturbationOperator final : public PerturbationOperator {
    GeneExpressionProgrammingGenotypeBlueprint* blueprint;
    double perturbation_rate;
    double chance_of_transposition;
    int transposition_max_length;
    IntegerGenerator* generator;
    DoubleGenerator* transposition_chance_generator;
public:
    GeneExpressionProgrammingPerturbationOperator(
        GeneExpressionProgrammingGenotypeBlueprint* blueprint,
        double perturbation_rate,
        double chance_of_transposition,
        int transposition_max_length
    );
    void perturbate(Genotype* genotype) override;
};



#endif //GENEEXPRESSIONPROGRAMMINGPERTURBATIONOPERATOR_H
