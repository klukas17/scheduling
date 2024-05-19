//
// Created by mihael on 5/7/24.
//

#include "OnlineSchedulerJobContext.h"

#include "MachinePathNode.h"
#include "ParallelGroupPathNode.h"
#include "RouteGroupPathNode.h"
#include "SerialGroupPathNode.h"
#include <limits>

#include "OpenGroupPathNode.h"

OnlineSchedulerJobContext::OnlineSchedulerJobContext(Job* job, OnlineSchedulingAlgorithmCluster* algorithm_cluster,OnlineSchedulerStepIdGenerator* step_id_generator) {
    this->job_id = job->getId();
    this->job = job;
    this->path_node_stack.push({job->getPathsRootNode()});
    this->current_processing_step = nullptr;
    this->algorithm_cluster = algorithm_cluster;
    this->step_id_generator = step_id_generator;
    this->simulator_state = nullptr;
}

JobProcessingStep* OnlineSchedulerJobContext::getNextProcessingStep() {
    if (path_node_stack.empty()) {
        return nullptr;
    }
    auto path_nodes = path_node_stack.top();
    path_node_stack.pop();

    PathNode* path_node = nullptr;
    if (path_nodes.size() > 1) {
        double score_next = -std::numeric_limits<double>::infinity();
        for (auto candidate_path_node : path_nodes) {
            auto params = new SchedulerParametersGroup(
                job->getReleaseTime(),
                job->getDueTime(),
                job->getWeight(),
                simulator_state->getTime(),
                simulator_state->calculateRemainingProcessingTimeInBranch(candidate_path_node),
                simulator_state->getNumberOfBranchPassings(candidate_path_node->getTopologyElement()->getId()),
                simulator_state->calculateNumberOfJobsInBranch(candidate_path_node->getTopologyElement()->getId()),
                simulator_state->calculateSpacesInBuffer(candidate_path_node->getTopologyElement()->getId()),
                simulator_state->checkPrerequisitesSatisfied(candidate_path_node)
            );
            double score = algorithms_cache[candidate_path_node->getTopologyElement()->getId()]->calculateScore(params);
            if (score > score_next) {
                score_next = score;
                path_node = candidate_path_node;
            }
        }
        std::vector<PathNode*> not_chosen_path_nodes;
        for (auto candidate : path_nodes) {
            if (candidate != path_node) {
                not_chosen_path_nodes.push_back(candidate);
            }
        }
        if (!not_chosen_path_nodes.empty()) {
            path_node_stack.push(not_chosen_path_nodes);
        }
    } else {
        path_node = path_nodes[0];
    }

    if (open_group_path_nodes.contains(path_node->getPathNodeId())) {
        simulator_state->addBranchPassingPoint(path_node->getTopologyElement()->getId());
    }

    switch (path_node->getTopologyElement()->getTopologyElementType()) {
    case ABSTRACT_TOPOLOGY_ELEMENT:
        {
            break;
        }
    case MACHINE_TOPOLOGY_ELEMENT:
        {
            auto machine_path_node = dynamic_cast<MachinePathNode*>(path_node);
            auto next = machine_path_node->getNext();
            if (next) {
                path_node_stack.push({next});
            }
            break;
        }
    case SERIAL_GROUP_TOPOLOGY_ELEMENT:
        {
            auto serial_group_path_node = dynamic_cast<SerialGroupPathNode*>(path_node);
            auto next = serial_group_path_node->getNext();
            if (next) {
                path_node_stack.push({next});
            }
            break;
        }
    case PARALLEL_GROUP_TOPOLOGY_ELEMENT:
        {
            auto parallel_group_path_node = dynamic_cast<ParallelGroupPathNode*>(path_node);
            auto machine_id = parallel_group_path_node->getTopologyElement()->getId();
            auto candidates_for_next = parallel_group_path_node->getNext();
            PathNode* next = nullptr;
            double score_next = -std::numeric_limits<double>::infinity();
            for (auto [_, path_node] : candidates_for_next) {
                auto params = new SchedulerParametersGroup(
                    job->getReleaseTime(),
                    job->getDueTime(),
                    job->getWeight(),
                    simulator_state->getTime(),
                    simulator_state->calculateRemainingProcessingTimeInBranch(path_node),
                    simulator_state->getNumberOfBranchPassings(path_node->getTopologyElement()->getId()),
                    simulator_state->calculateNumberOfJobsInBranch(path_node->getTopologyElement()->getId()),
                    simulator_state->calculateSpacesInBuffer(path_node->getTopologyElement()->getId()),
                    simulator_state->checkPrerequisitesSatisfied(path_node)
                );
                double score = algorithm_cluster->getAlgorithm(machine_id)->calculateScore(params);
                if (score > score_next) {
                    score_next = score;
                    next = path_node;
                }
            }
            if (next) {
                simulator_state->addBranchPassingPoint(next->getTopologyElement()->getId());
                path_node_stack.push({next});
            }
            break;
        }
    case ROUTE_GROUP_TOPOLOGY_ELEMENT:
        {
            auto route_group_path_node = dynamic_cast<RouteGroupPathNode*>(path_node);
            auto next = route_group_path_node->getNext();
            if (next) {
                path_node_stack.push({next});
            }
            break;
        }
    case OPEN_GROUP_TOPOLOGY_ELEMENT:
        {
            auto open_group_path_node = dynamic_cast<OpenGroupPathNode*>(path_node);
            auto machine_id = open_group_path_node->getTopologyElement()->getId();
            auto next = open_group_path_node->getNext();
            if (next) {
                path_node_stack.push({next});
            }
            auto sub_path_node_entries = open_group_path_node->getSubPathNodes();
            std::vector<PathNode*> sub_path_nodes;
            for (auto [id, sub_path_node] : sub_path_node_entries) {
                sub_path_nodes.push_back(sub_path_node);
                algorithms_cache[sub_path_node->getTopologyElement()->getId()] = algorithm_cluster->getAlgorithm(machine_id);
            }
            if (!sub_path_nodes.empty()) {
                path_node_stack.push(sub_path_nodes);
            }
            for (auto sub_path_node : sub_path_nodes) {
                open_group_path_nodes.insert(sub_path_node->getPathNodeId());
            }
            break;
        }
    }
    auto step_id = step_id_generator->generate_step_id();
    auto job_processing_step = new JobProcessingStep(step_id, path_node->getTopologyElement()->getId(), job_id, path_node->getPathNodeId());
    processing_steps_map[step_id] = job_processing_step;
    return job_processing_step;
}

JobProcessingStep* OnlineSchedulerJobContext::getProcessingStep(long step_id) {
    return processing_steps_map[step_id];
}

bool OnlineSchedulerJobContext::checkHasJobFinished() {
    return path_node_stack.empty();
}

void OnlineSchedulerJobContext::setSimulatorState(SimulatorState* simulator_state) {
    this->simulator_state = simulator_state;
}
