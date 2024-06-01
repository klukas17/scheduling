//
// Created by mihael on 5/31/24.
//

#ifndef STRUCTUREDGRAMMATICALEVOLUTIONPERTURBATIONOPERATOR_H
#define STRUCTUREDGRAMMATICALEVOLUTIONPERTURBATIONOPERATOR_H
#include "PerturbationOperator.h"
#include "StructuredGrammaticalEvolutionGenotypeBlueprint.h"


class StructuredGrammaticalEvolutionPerturbationOperator final : public PerturbationOperator {
    StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint;
    double perturbation_rate;
    IntegerGenerator* generator;
public:
    StructuredGrammaticalEvolutionPerturbationOperator(StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint, double perturbation_rate);
    void perturbate(Genotype* genotype) override;
};



#endif //STRUCTUREDGRAMMATICALEVOLUTIONPERTURBATIONOPERATOR_H
