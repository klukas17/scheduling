//
// Created by mihael on 9/16/23.
//

#include "JobProcessingPrerequisites.h"
#include "algorithm"

JobProcessingPrerequisites::JobProcessingPrerequisites(long const job_id, long const machine_id, long const step_id, const std::vector<Prerequisite *>& prerequisites) {
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

void JobProcessingPrerequisites::updatePrerequisites(long const machine_id, long const job_id, long const repetitions) {
    for (int i = 0; i < prerequisites.size(); i++) {
        if (auto const prerequisite = prerequisites[i]; job_id == prerequisite->getJobId() && machine_id == prerequisite->getMachineId() && repetitions >= prerequisite->getRepetitions()) {
            prerequisites_satisfied[i] = true;
        }
    }
}

bool JobProcessingPrerequisites::checkAllPrerequisitesSatisfied() {
    if (!std::ranges::all_of(prerequisites_satisfied, [](const auto& prerequisite_satisfied) { return prerequisite_satisfied; })) {
        return false;
    }
    return true;
}