//
// Created by mihael on 5/2/24.
//

#include "OnlineSchedulingAlgorithm.h"

std::vector<std::string> OnlineSchedulingAlgorithm::group_inputs = {
    "release_time",
    "due_time",
    "weight",
    "time",
    "remaining_processing_time_in_branch",
    "number_of_jobs_passed_through_a_machine",
    "number_of_jobs_in_branch"
};

std::vector<std::string> OnlineSchedulingAlgorithm::machine_inputs = {
    "release_time",
    "due_time",
    "weight",
    "time",
    "combined_weights_of_batch_compatible_jobs",
    "number_of_batch_compatible_jobs"
};

void OnlineSchedulingAlgorithm::setInputs(GeneralTopologyElementType general_topology_element_type) {
    switch (general_topology_element_type) {
    case ABSTRACT_GENERAL_TOPOLOGY_ELEMENT:
        this->inputs = {};
        break;

    case GROUP_GENERAL_TOPOLOGY_ELEMENT:
        this->inputs = group_inputs;
        break;

    case MACHINE_GENERAL_TOPOLOGY_ELEMENT:
        this->inputs = machine_inputs;
        break;
    }
}

double OnlineSchedulingAlgorithm::calculateScore(SchedulerParametersGroup* group_params) {
    std::map<std::string, double> params;
    params["release_time"] = group_params->release_time;
    params["due_time"] = group_params->due_time;
    params["weight"] = group_params->weight;
    params["time"] = group_params->time;
    params["remaining_processing_time_in_branch"] = group_params->remaining_processing_time_in_branch;
    params["number_of_jobs_passed_through_a_machine"] = group_params->number_of_jobs_passed_through_a_machine;
    params["number_of_jobs_in_branch"] = group_params->number_of_jobs_in_branch;
    // delete group_params;
    return calculateScore(params);
}

double OnlineSchedulingAlgorithm::calculateScore(SchedulerParametersMachine* machine_params) {
    std::map<std::string, double> params;
    params["release_time"] = machine_params->release_time;
    params["due_time"] = machine_params->due_time;
    params["weight"] = machine_params->weight;
    params["time"] = machine_params->time;
    params["combined_weights_of_batch_compatible_jobs"] = machine_params->combined_weights_of_batch_compatible_jobs;
    params["number_of_batch_compatible_jobs"] = machine_params->number_of_batch_compatible_jobs;
    // delete machine_params;
    return calculateScore(params);
}

