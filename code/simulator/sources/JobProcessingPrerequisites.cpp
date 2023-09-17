//
// Created by mihael on 9/16/23.
//

/**
 * @file JobProcessingPrerequisites.cpp
 * @brief Implements the member functions of the JobProcessingPrerequisites class.
 */

#include "JobProcessingPrerequisites.h"

JobProcessingPrerequisites::JobProcessingPrerequisites(long job_id, long machine_id, long step_id, const std::vector<Prerequisite *>& prerequisites) {
    this->job_id = job_id;
    this->machine_id = machine_id;
    this->step_id = step_id;
    this->prerequisites = prerequisites;
    for (int i = 0; i < prerequisites.size(); i++) {
        prerequisites_satisfied.push_back(false);
    }
}

long JobProcessingPrerequisites::getJobId() const {
    return job_id;
}

long JobProcessingPrerequisites::getMachineId() const {
    return machine_id;
}

long JobProcessingPrerequisites::getStepId() const {
    return step_id;
}

void JobProcessingPrerequisites::updatePrerequisites(long machine_id, long job_id, long repetitions) {
    for (int i = 0; i < prerequisites.size(); i++) {
        auto prerequisite = prerequisites[i];
        if (job_id == prerequisite->getJobId() && machine_id == prerequisite->getMachineId() && repetitions >= prerequisite->getRepetitions()) {
            prerequisites_satisfied[i] = true;
        }
    }
}

bool JobProcessingPrerequisites::checkAllPrerequisitesSatisfied() {
    for (auto && prerequisite_satisfied : prerequisites_satisfied) {
        if (!prerequisite_satisfied) {
            return false;
        }
    }
    return true;
}