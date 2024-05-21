//
// Created by mihael on 5/20/24.
//

#include "RegressionFunction.h"
#include <utility>
#include "fstream"
#include "sstream"
#include "OnlineSchedulingAlgorithm.h"

RegressionFunction::RegressionFunction(bool minimization, std::vector<std::string> params, std::string path) : EvaluationFunction(minimization) {
    this->params = std::move(params);
    loadData(path);
}

void RegressionFunction::loadData(std::string path) {
    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line)) {
        if (line.starts_with("#")) {
            continue;
        }

        std::vector<double> numbers;

        std::istringstream iss(line);
        double num;
        while (iss >> num) {
            numbers.push_back(num);
        }

        this->data.push_back(numbers);
    }

    file.close();
}

double RegressionFunction::_evaluate(Genotype* genotype) {
    auto alg = dynamic_cast<OnlineSchedulingAlgorithm*>(genotype);

    alg->setInputs(this->params);

    double error = 0;

    for (auto line : data) {
        std::map<std::string, double> params;
        for (int i = 0; i < this->params.size(); i++) {
            params[this->params[i]] = line[i];
        }

        auto score = alg->calculateScore(params);
        auto expected = line.back();
        auto diff = expected - score;

        error += diff * diff;
    }

    return error;
}


