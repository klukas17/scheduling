//
// Created by mihael on 6/3/24.
//

#ifndef HYPERPARAMETERTUNINGGENOTYPE_H
#define HYPERPARAMETERTUNINGGENOTYPE_H

#include <map>
#include <string>
#include <vector>
#include "Genotype.h"
#include "HyperparameterTuningTypes.h"


class HyperparameterTuningGenotype final : public Genotype {
public:
    std::vector<std::string> hyperparameters;
    std::map<std::string, hyperparameter_value> hyperparameter_values;
    HyperparameterTuningGenotype(std::vector<std::string> hyperparameters, std::map<std::string, hyperparameter_value> hyperparameter_values);
    Genotype* copy() override;
};



#endif //HYPERPARAMETERTUNINGGENOTYPE_H
