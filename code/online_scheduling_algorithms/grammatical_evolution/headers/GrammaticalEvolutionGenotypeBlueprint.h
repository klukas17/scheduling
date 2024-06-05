//
// Created by mihael on 5/30/24.
//

#ifndef GRAMMATICALEVOLUTIONGENOTYPEBLUEPRINT_H
#define GRAMMATICALEVOLUTIONGENOTYPEBLUEPRINT_H
#include <string>
#include <vector>

#include "DoubleGenerator.h"
#include "GEGrammar.h"
#include "IntegerGenerator.h"
#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"


class GrammaticalEvolutionGenotypeBlueprint final : public OnlineSchedulingAlgorithmGenotypeBlueprint {
public:
    int codons;
    int codon_values;
    int max_number_of_wrapping;
    GEGrammar* grammar;
    DoubleGenerator* constant_generator;
    IntegerGenerator* generator;
    GrammaticalEvolutionGenotypeBlueprint(
        int codons,
        int codon_values,
        int max_number_of_wrapping,
        double constant_min,
        double constant_max
    );
    ~GrammaticalEvolutionGenotypeBlueprint() override;
    double generateConstant();
    std::string generateParam(std::vector<std::string> params);
    int generateCodonValue();
};



#endif //GRAMMATICALEVOLUTIONGENOTYPEBLUEPRINT_H
