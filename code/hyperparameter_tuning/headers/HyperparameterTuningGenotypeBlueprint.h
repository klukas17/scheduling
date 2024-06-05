//
// Created by mihael on 6/3/24.
//

#ifndef HYPERPARAMETERTUNINGGENOTYPEBLUEPRINT_H
#define HYPERPARAMETERTUNINGGENOTYPEBLUEPRINT_H
#include <map>
#include <string>
#include <vector>

#include "GenotypeBlueprint.h"
#include "HyperparameterTuningTypes.h"
#include "IntegerGenerator.h"


class HyperparameterTuningGenotypeBlueprint final : public GenotypeBlueprint {
public:
    std::vector<std::string> hyperparameters;
    std::map<std::string, std::vector<hyperparameter_value>> hyperparameter_domains;
    IntegerGenerator* generator;
    HyperparameterTuningGenotypeBlueprint(
        std::vector<std::string> hyperparameters,
        std::map<std::string, std::vector<hyperparameter_value>> hyperparameter_domains
    );
    hyperparameter_value generateHyperparameterValue(const std::string& hyperparameter);
};



#endif //HYPERPARAMETERTUNINGGENOTYPEBLUEPRINT_H
