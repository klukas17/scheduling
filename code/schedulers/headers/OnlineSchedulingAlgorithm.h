//
// Created by mihael on 5/2/24.
//

#ifndef ONLINESCHEDULINGALGORITHM_H
#define ONLINESCHEDULINGALGORITHM_H

#include <map>
#include <string>
#include <vector>

#include "Genotype.h"
#include "SchedulerParametersGroup.h"
#include "SchedulerParametersMachine.h"
#include "TopologyElementType.h"

class OnlineSchedulingAlgorithm : public Genotype {
protected:
    virtual double calculateScore(std::map<std::string, double> params) = 0;
    std::vector<std::string> inputs;
    static std::vector<std::string> group_inputs;
    static std::vector<std::string> machine_inputs;
public:
    void setInputs(GeneralTopologyElementType general_topology_element_type);
    double calculateScore(SchedulerParametersGroup* group_params);
    double calculateScore(SchedulerParametersMachine* machine_params);
};



#endif //ONLINESCHEDULINGALGORITHM_H
