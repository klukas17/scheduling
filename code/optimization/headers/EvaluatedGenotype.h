//
// Created by mihael on 4/4/24.
//

#ifndef EVALUATEDGENOTYPE_H
#define EVALUATEDGENOTYPE_H

#include "Genotype.h"

class EvaluatedGenotype {
public:
    Genotype* genotype;
    double fitness_score;
    EvaluatedGenotype(Genotype* genotype, double fitness_score);
    ~EvaluatedGenotype();
};



#endif //EVALUATEDGENOTYPE_H
