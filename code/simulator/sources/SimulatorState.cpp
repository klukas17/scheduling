//
// Created by mihael on 5/11/24.
//

#include "SimulatorState.h"
#include <ranges>
#include "Machine.h"
#include "iostream"
#include "MachinePathNode.h"
#include "OpenGroupPathNode.h"
#include "ParallelGroupPathNode.h"
#include "RouteGroupPathNode.h"
#include "SerialGroup.h"
#include "SerialGroupPathNode.h"
#include <limits>
#include <utility>

SimulatorState::SimulatorState(const std::map<long, Job*>& jobs, Topology* topology) {
    this->jobs = jobs;
    this->topology = topology;
    this->time = 0;
    for (auto job_id : jobs | std::ranges::views::keys) {
        job_info_map[job_id] = new SimulatorStateJobInfo();
    }
    for (auto [machine_id, topology_element] : topology->getTopologyElementsMap()) {
        auto breakdowns_vector = topology_element->getBreakdowns();
        std::deque<Breakdown*> breakdowns(breakdowns_vector.begin(), breakdowns_vector.end());
        breakdowns_map[machine_id] = breakdowns;
    }
}

SimulatorState::~SimulatorState() {
    for (auto job_info_key : job_info_map | std::views::keys) {
        delete job_info_map[job_info_key];
    }
}

double SimulatorState::getTime() {
    return time;
}

void SimulatorState::setTime(double time) {
    this->time = time;
}

void SimulatorState::setMachineProcessingContextMap(std::map<long, MachineProcessingContext*> machine_processing_context_map) {
    this->machine_processing_context_map = std::move(machine_processing_context_map);
}


Job* SimulatorState::getJob(long job_id) {
    return jobs[job_id];
}

void SimulatorState::setJobOnMachine(long machine_id, long job_id) {
    jobs_in_machines_map[machine_id].insert(job_id);
}

void SimulatorState::machineEntry(long machine_id, long job_id, double remaining_time_on_machine) {
    auto job_info = job_info_map[job_id];
    job_info->setMachineId(machine_id);
    job_info->setCurrentlyProcessingOnMachine(true);
    job_info->setRemainingTimeOnMachine(remaining_time_on_machine);
    job_info->setStartOfProcessingTime(time);
}

void SimulatorState::machineExit(long machine_id, long job_id) {
    auto job_info = job_info_map[job_id];
    job_info->setMachineId(0);
    job_info->setCurrentlyProcessingOnMachine(false);
    job_info->setRemainingTimeOnMachine(0);
    job_info->setStartOfProcessingTime(0);
    jobs_in_machines_map[machine_id].erase(job_id);
}

void SimulatorState::machineBufferEntry(long machine_id, long job_id, double remaining_time_on_machine) {
    auto job_info = job_info_map[job_id];
    job_info->setMachineId(machine_id);
    job_info->setCurrentlyProcessingOnMachine(false);
    job_info->setRemainingTimeOnMachine(remaining_time_on_machine);
    job_info->setStartOfProcessingTime(0);
    jobs_in_machines_map[machine_id].insert(job_id);
}

void SimulatorState::preempt(long machine_id, long job_id, double remaining_time_on_machine) {
    auto job_info = job_info_map[job_id];
    job_info->setMachineId(machine_id);
    job_info->setCurrentlyProcessingOnMachine(false);
    job_info->setRemainingTimeOnMachine(remaining_time_on_machine);
    job_info->setStartOfProcessingTime(0);
}

double SimulatorState::calculateCombinedWeightsOfBatchCompatibleJobs(long machine_id, long job_id) {
    auto compatible_jobs = calculateBatchCompatibleJobs(machine_id, job_id);
    double result = 0;
    for (auto job : compatible_jobs) {
        result += job->getWeight();
    }
    return result;
}

int SimulatorState::calculateNumberOfBatchCompatibleJobs(long machine_id, long job_id) {
    auto compatible_jobs = calculateBatchCompatibleJobs(machine_id, job_id);
    return compatible_jobs.size();
}

std::vector<Job*> SimulatorState::calculateBatchCompatibleJobs(long machine_id, long job_id) {
    auto job = jobs[job_id];
    auto job_type_id = job->getJobType()->getId();
    auto element = topology->getTopologyElementsMap().at(machine_id);
    if (element->getTopologyElementType() != MACHINE_TOPOLOGY_ELEMENT) {
        return {};
    }
    auto machine = dynamic_cast<Machine*>(element);
    auto batch_processing_scenario_rules = machine->getMachineType()->getBatchProcessingScenarioRules();
    auto batch_processing_scenario = batch_processing_scenario_rules->findBatchProcessingScenario(job_type_id);
    if (batch_processing_scenario == nullptr) {
        return {};
    }
    std::vector<Job*> candidates;
    auto job_remaining_processing_time = job_info_map[job_id]->calculateRemainingTime(time);
    for (auto candidate_id : jobs_in_machines_map[machine_id]) {
        if (candidate_id == job_id) {
            continue;
        }
        auto candidate = jobs[candidate_id];
        auto candidate_type_id = candidate->getJobType()->getId();
        if (job_type_id != candidate_type_id) {
            continue;
        }
        auto candidate_remaining_processing_time = job_info_map[candidate_id]->calculateRemainingTime(time);
        if (job_remaining_processing_time == candidate_remaining_processing_time) {
            candidates.push_back(candidate);
        }
    }
    return candidates;
}

void SimulatorState::addBranchPassingPoint(long machine_id) {
    if (!branch_passing_map.contains(machine_id)) {
        branch_passing_map[machine_id] = 0;
    }
    branch_passing_map[machine_id]++;
}

int SimulatorState::getNumberOfBranchPassings(long machine_id) {
    return branch_passing_map[machine_id];
}

int SimulatorState::calculateNumberOfJobsInBranch(long machine_id) {
    int result = jobs_in_machines_map[machine_id].size();
    auto topology_element = topology->getTopologyElementsMap().at(machine_id);
    switch (topology_element->getGeneralTopologyElementType()) {
    case ABSTRACT_GENERAL_TOPOLOGY_ELEMENT:
    case MACHINE_GENERAL_TOPOLOGY_ELEMENT:
        break;

    case GROUP_GENERAL_TOPOLOGY_ELEMENT:
        auto group = dynamic_cast<Group*>(topology_element);
        for (auto child : group->getChildren()) {
            result += calculateNumberOfJobsInBranch(child->getId());
        }
    }
    return result;
}

double SimulatorState::calculateRemainingProcessingTimeInBranch(PathNode* path_node) {
    return calculateRemainingProcessingTimeForPathNode(path_node, nullptr, 0);
}

double SimulatorState::calculateRemainingProcessingTimeForPathNode(PathNode* path_node, PathNode* prev_path_node, double diff) {

    if (path_node->getTopologyElement()->getTopologyElementType() == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        auto parallel_group_path_node = dynamic_cast<ParallelGroupPathNode*>(path_node);
        auto next = parallel_group_path_node->getNext();
        for (auto next_path_node : next | std::views::values) {
            if (next_path_node == prev_path_node) {
                diff += prev_path_node->getRemainingProcessingTime() - parallel_group_path_node->getRemainingProcessingTime();
                break;
            }
        }
    }

    auto predecessors = path_node->getPredecessors();
    if (predecessors.empty()) {
        return path_node->getRemainingProcessingTime() + diff;
    }
    auto result = std::numeric_limits<double>::infinity();
    for (auto predecessor : predecessors) {
        result = std::min(result, calculateRemainingProcessingTimeForPathNode(predecessor, path_node, diff));
    }
    return result;
}

bool SimulatorState::calculatePreemptAllowed(long machine_id, long job_id) {
    auto topology_element = topology->getTopologyElementsMap().at(machine_id);
    if (topology_element->getTopologyElementType() != MACHINE_TOPOLOGY_ELEMENT) {
        return false;
    }
    auto machine = dynamic_cast<Machine*>(topology_element);
    auto job = jobs.at(job_id);
    return machine->getMachineType()->getPreempt() && job->getJobType()->getPreempt();
}

double SimulatorState::calculateTimeUntilNextBreakdown(long machine_id) {
    std::deque<Breakdown*>& breakdowns = breakdowns_map[machine_id];
    while (!breakdowns.empty() && breakdowns[0]->getStartTime() < time) {
        breakdowns.pop_front();
    }
    if (breakdowns.empty()) {
        return std::numeric_limits<double>::infinity();
    } else {
        return breakdowns[0]->getStartTime() - time;
    }
}

double SimulatorState::calculateSetupLength(long machine_id, long job_id) {
    auto topology_element = topology->getTopologyElementsMap().at(machine_id);
    if (topology_element->getTopologyElementType() != MACHINE_TOPOLOGY_ELEMENT) {
        return 0;
    }
    auto machine = dynamic_cast<Machine*>(topology_element);
    auto machine_processing_context = machine_processing_context_map[machine_id];
    auto setup_rules = machine->getMachineType()->getSetupRules();
    auto last_job_type = machine_processing_context->getLastJobType();
    auto job_type = jobs.at(job_id)->getJobType();
    auto setup = setup_rules->findSetup(last_job_type ? last_job_type->getId() : -1, job_type->getId());
    if (setup) {
        return setup->getDuration();
    } else {
        return 0;
    }
}
