//
// Created by mihael on 5/6/24.
//

#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "CreationOperator.h"
#include "EvaluatedGenotype.h"
#include "EvaluationFunction.h"


class Population {
    int population_size;
    std::vector<EvaluatedGenotype*> population;
    static bool (*comparator)(EvaluatedGenotype*, EvaluatedGenotype*);
public:
    explicit Population(int population_size);
    void initialize(CreationOperator* creation_operator, EvaluationFunction* evaluation_function);
    EvaluatedGenotype* getGenotype(int index);
    void insertGenotype(EvaluatedGenotype* genotype);
};



#endif //POPULATION_H
