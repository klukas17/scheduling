//
// Created by mihael on 5/31/24.
//

#ifndef STRUCTUREDGRAMMATICALEVOLUTIONGENOTYPEBLUEPRINT_H
#define STRUCTUREDGRAMMATICALEVOLUTIONGENOTYPEBLUEPRINT_H
#include "DoubleGenerator.h"
#include "IntegerGenerator.h"
#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"
#include "SGEGrammar.h"


class StructuredGrammaticalEvolutionGenotypeBlueprint final : public OnlineSchedulingAlgorithmGenotypeBlueprint {
public:
    int max_depth;
    SGEGrammar* grammar;
    DoubleGenerator* constant_generator;
    IntegerGenerator* generator;
    StructuredGrammaticalEvolutionGenotypeBlueprint(
        int max_depth,
        double constant_min,
        double constant_max
    );
    double generateConstant();
    int generateCodonValue(int possible_values);
};



#endif //STRUCTUREDGRAMMATICALEVOLUTIONGENOTYPEBLUEPRINT_H
