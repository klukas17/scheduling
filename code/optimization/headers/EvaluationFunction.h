//
// Created by mihael on 2/16/24.
//

#ifndef EVALUATIONFUNCTION_H
#define EVALUATIONFUNCTION_H

#include "Genotype.h"


class EvaluationFunction {
    int evaluation_factor;
public:
    explicit EvaluationFunction(bool minimization);
    double evaluate(Genotype* genotype);
    virtual double _evaluate(Genotype* genotype) = 0;
    virtual ~EvaluationFunction() = 0;
};


#endif //EVALUATIONFUNCTION_H
