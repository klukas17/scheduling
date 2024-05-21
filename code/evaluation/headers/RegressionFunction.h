//
// Created by mihael on 5/20/24.
//

#ifndef REGRESSIONFUNCTION_H
#define REGRESSIONFUNCTION_H
#include <string>
#include <vector>

#include "EvaluationFunction.h"


class RegressionFunction final : public EvaluationFunction {
    std::vector<std::string> params;
    std::vector<std::vector<double>> data;
public:
    RegressionFunction(bool minimization, std::vector<std::string> params, std::string path);
    void loadData(std::string path);
    double _evaluate(Genotype* genotype) override;
};



#endif //REGRESSIONFUNCTION_H
