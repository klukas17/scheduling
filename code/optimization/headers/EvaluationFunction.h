//
// Created by mihael on 2/16/24.
//

#ifndef EVALUATIONFUNCTION_H
#define EVALUATIONFUNCTION_H

#include "Genotype.h"


class EvaluationFunction {
private:
    int evaluation_factor;
    virtual double _evaluate(Genotype* genotype) = 0;
public:
    explicit EvaluationFunction(bool minimization);
    double evaluate(Genotype* genotype);
    virtual ~EvaluationFunction() = 0;
};


#endif //EVALUATIONFUNCTION_H
