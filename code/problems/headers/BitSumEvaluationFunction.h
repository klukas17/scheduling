//
// Created by mihael on 2/18/24.
//

#ifndef BITSUMEVALUATIONFUNCTION_H
#define BITSUMEVALUATIONFUNCTION_H

#include "EvaluationFunction.h"

class BitSumEvaluationFunction final : public EvaluationFunction {
public:
    explicit BitSumEvaluationFunction(bool minimization);
    double _evaluate(Genotype* genotype) override;
};



#endif //BITSUMEVALUATIONFUNCTION_H
