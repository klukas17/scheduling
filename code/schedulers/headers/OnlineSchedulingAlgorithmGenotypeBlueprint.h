//
// Created by mihael on 5/20/24.
//

#ifndef ONLINESCHEDULINGALGORITHMGENOTYPEBLUEPRINT_H
#define ONLINESCHEDULINGALGORITHMGENOTYPEBLUEPRINT_H
#include <string>
#include <vector>

#include "GenotypeBlueprint.h"


class OnlineSchedulingAlgorithmGenotypeBlueprint : public GenotypeBlueprint {
protected:
    std::vector<std::string> inputs;
public:
    OnlineSchedulingAlgorithmGenotypeBlueprint();
    std::vector<std::string> getInputs();
    void setInputs(std::vector<std::string> inputs);
};



#endif //ONLINESCHEDULINGALGORITHMGENOTYPEBLUEPRINT_H
