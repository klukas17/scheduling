//
// Created by mihael on 4/4/24.
//

#include "EvaluatedGenotype.h"

EvaluatedGenotype::EvaluatedGenotype(Genotype* genotype, double const fitness_score) {
    this->genotype = genotype;
    this->fitness_score = fitness_score;
}

EvaluatedGenotype::~EvaluatedGenotype() {
    delete genotype;
}
