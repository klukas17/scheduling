//
// Created by mihael on 9/2/23.
//

#include "JobProcessingContext.h"
#include "SchedulingError.h"
#include "MachinePathNode.h"
#include "SerialGroupPathNode.h"
#include "ParallelGroupPathNode.h"
#include "RouteGroupPathNode.h"
#include "OpenGroupPathNode.h"

#include "iostream"

JobProcessingContext::JobProcessingContext(Job* job) {
    this->job = job;
    this->path_node = job->getPathsRootNode();
    this->prev_path_node = nullptr;
    this->job_processing_step = nullptr;
    this->last_processed_path_node_id = -1;
    this->processing_started = false;
    this->previous_machine_processing_context = nullptr;
}

JobProcessingContext::~JobProcessingContext() {
    while (!frames.empty()) {
        auto const frame = frames.top();
        frames.pop();
        delete frame;
    }
}

Job *JobProcessingContext::getJob() const {
    return job;
}

PathNode *JobProcessingContext::getPathNode() const {
    return path_node;
}

void JobProcessingContext::setJobProcessingStep(JobProcessingStep *job_processing_step) {
    if (this->job_processing_step) {
        delete this->job_processing_step;
        this->job_processing_step = nullptr;
    }
    this->job_processing_step = job_processing_step;
}

void JobProcessingContext::moveToNextPathNode(long const next_machine_id) {

    if (!path_node || job_processing_step->getMachineId() != next_machine_id) {
        throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
    }

    prev_path_node = path_node;

    if (processing_started && path_node->getTopologyElement()->getTopologyElementType() == PARALLEL_GROUP_TOPOLOGY_ELEMENT && last_processed_path_node_id == path_node->getPathNodeId()) {
        auto const parallel_group_path_node = dynamic_cast<ParallelGroupPathNode*>(path_node);
        PathNode* next_path_node = nullptr;
        for (auto const [candidate_next_id, candidate_next] : parallel_group_path_node->getNext()) {
            if (candidate_next_id == next_machine_id) {
                next_path_node = candidate_next;
                break;
            }
        }
        if (!next_path_node) {
            throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
        }
        path_node = next_path_node;
        prev_path_node = next_path_node;
    }

    if (processing_started && path_node->getTopologyElement()->getTopologyElementType() == OPEN_GROUP_TOPOLOGY_ELEMENT && last_processed_path_node_id == path_node->getPathNodeId() && !frames.empty() && frames.top()->getOpenGroupPathTreeNode()->getPathNode()->getPathNodeId() == path_node->getPathNodeId()) {
        PathNode* next_path_node = nullptr;
        for (auto const candidate_sub_path_node : dynamic_cast<OpenGroupPathTreeNode*>(job->getPathTreeNode(path_node->getPathNodeId()))->getChildren()) {
            if (candidate_sub_path_node->getPathNode()->getPathNodeId() == job_processing_step->getPathNodeId()) {
                next_path_node = candidate_sub_path_node->getPathNode();
                break;
            }
        }
        if (!next_path_node) {
            throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
        }
        frames.top()->visitChild(job_processing_step->getPathNodeId());
        path_node = next_path_node;
        prev_path_node = next_path_node;
    }

    if (!processing_started) {
        processing_started = true;
    }

    last_processed_path_node_id = path_node->getPathNodeId();

    switch (path_node->getTopologyElement()->getTopologyElementType()) {

        case ABSTRACT_TOPOLOGY_ELEMENT: {
            throw SchedulingError("Abstract topology element encountered in JobProcessingContext::moveToNextPathNode function.");
        }

        case MACHINE_TOPOLOGY_ELEMENT: {
            auto const machine_path_node = dynamic_cast<MachinePathNode*>(path_node);
            if (path_node->getTopologyElement()->getId() != next_machine_id) {
                throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
            }
            path_node = machine_path_node->getNext();
            break;
        }

        case SERIAL_GROUP_TOPOLOGY_ELEMENT: {
            auto const serial_group_path_node = dynamic_cast<SerialGroupPathNode*>(path_node);
            if (path_node->getTopologyElement()->getId() != next_machine_id) {
                throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
            }
            path_node = serial_group_path_node->getNext();
            break;
        }

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT: {
            if (path_node->getTopologyElement()->getId() != next_machine_id) {
                throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
            }
            break;
        }

        case ROUTE_GROUP_TOPOLOGY_ELEMENT: {
            auto const route_group_path_node = dynamic_cast<RouteGroupPathNode*>(path_node);
            if (path_node->getTopologyElement()->getId() != next_machine_id) {
                throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
            }
            path_node = route_group_path_node->getNext();
            break;
        }

        case OPEN_GROUP_TOPOLOGY_ELEMENT: {
            auto const open_group_path_node = dynamic_cast<OpenGroupPathNode*>(path_node);
            if (path_node->getTopologyElement()->getId() != next_machine_id) {
                throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
            }
            if (open_group_path_node->getSubPathNodes().empty()) {
                path_node = open_group_path_node->getNext();
            }
            else {
                auto const frame = new JobProcessingContextFrame(dynamic_cast<OpenGroupPathTreeNode*>(job->getPathTreeNode(open_group_path_node->getPathNodeId())));
                frames.push(frame);
            }
            break;
        }
    }

    while (!path_node && !frames.empty()) {
        path_node = frames.top()->getOpenGroupPathTreeNode()->getPathNode();
        last_processed_path_node_id = path_node->getPathNodeId();
        if (frames.top()->checkAllChildrenVisited()) {
            auto const frame = frames.top();
            frames.pop();
            delete frame;
            path_node = dynamic_cast<OpenGroupPathNode*>(path_node)->getNext();
        }
    }

}

bool JobProcessingContext::checkIfPathFinished() const {
    return !path_node && !job_processing_step && frames.empty();
}

MachineProcessingContext *JobProcessingContext::getPreviousMachineProcessingContext() const {
    return previous_machine_processing_context;
}

void JobProcessingContext::setPreviousMachineProcessingContext(MachineProcessingContext *previous_machine_processing_context) {
    this->previous_machine_processing_context = previous_machine_processing_context;
}

void JobProcessingContext::markCurrentPathNodeAsCompleted() {
    auto processing_time = job->getProcessingTime(prev_path_node->getTopologyElement()->getId());
    if (processing_time == 0) {
        return;
    }
    std::map<long, double> applied_diffs_map;
    reduceRemainingProcessingTime(prev_path_node, processing_time, applied_diffs_map);
}

void JobProcessingContext::reduceRemainingProcessingTime(PathNode* path_node, double diff, std::map<long, double>& applied_diffs_map) {

    if (path_node->getTopologyElement()->getTopologyElementType() == PARALLEL_GROUP_TOPOLOGY_ELEMENT) {
        auto parallel_group_path_node = dynamic_cast<ParallelGroupPathNode*>(path_node);
        auto old_remaining_time = parallel_group_path_node->getRemainingProcessingTime();
        auto new_remaining_time = parallel_group_path_node->getRemainingProcessingTime();
        for (auto [_, next] : parallel_group_path_node->getNext()) {
            new_remaining_time = std::min(new_remaining_time, next->getRemainingProcessingTime());
        }
        diff = old_remaining_time - new_remaining_time;
    }

    if (diff <= 0) {
        return;
    }

    auto path_node_id = path_node->getPathNodeId();

    if (!applied_diffs_map.contains(path_node_id)) {
        applied_diffs_map[path_node_id] = 0;
    }

    auto applied_diff = applied_diffs_map[path_node_id];
    auto delta_diff = diff - applied_diff;

    if (delta_diff <= 0) {
        return;
    }

    applied_diffs_map[path_node_id] = diff;
    path_node->setRemainingProcessingTime(path_node->getRemainingProcessingTime() - delta_diff);
    for (auto predecessor : path_node->getPredecessors()) {
        reduceRemainingProcessingTime(predecessor, diff, applied_diffs_map);
    }
}

void JobProcessingContext::logRemainingProcessingTimes() {
    std::set<long> visited;
    logRemainingProcessingTimesForPathNode(job->getPathsRootNode(), visited);
    std::cout << std::endl;
}

void JobProcessingContext::logRemainingProcessingTimesForPathNode(PathNode* node, std::set<long>& visited) {

    long path_node_id = node->getPathNodeId();
    if (visited.contains(path_node_id)) {
        return;
    }
    visited.insert(path_node_id);

    switch(node->getTopologyElement()->getTopologyElementType()) {
    case ABSTRACT_TOPOLOGY_ELEMENT: {
            break;
    }

    case MACHINE_TOPOLOGY_ELEMENT: {
            auto machine_path_node = dynamic_cast<MachinePathNode*>(node);
            std::cout << "Machine " << machine_path_node->getTopologyElement()->getId() << " = ";
            std::cout << machine_path_node->getRemainingProcessingTime();
            std::cout << std::endl;
            auto next = machine_path_node->getNext();
            if (next) {
                logRemainingProcessingTimesForPathNode(next, visited);
            }
            break;
    }

    case SERIAL_GROUP_TOPOLOGY_ELEMENT: {
            auto serial_group_path_node = dynamic_cast<SerialGroupPathNode*>(node);
            std::cout << "Serial group " << serial_group_path_node->getTopologyElement()->getId() << " = ";
            std::cout << serial_group_path_node->getRemainingProcessingTime();
            std::cout << std::endl;
            auto next = serial_group_path_node->getNext();
            if (next) {
                logRemainingProcessingTimesForPathNode(next, visited);
            }
            break;
    }

    case PARALLEL_GROUP_TOPOLOGY_ELEMENT: {
            auto paralell_group_path_node = dynamic_cast<ParallelGroupPathNode*>(node);
            std::cout << "Parallel group " << paralell_group_path_node->getTopologyElement()->getId() << " = ";
            std::cout << paralell_group_path_node->getRemainingProcessingTime();
            std::cout << std::endl;
            for (auto [_, next] : paralell_group_path_node->getNext()) {
                logRemainingProcessingTimesForPathNode(next, visited);
            }
            break;
    }

    case ROUTE_GROUP_TOPOLOGY_ELEMENT: {
            auto route_group_path_node = dynamic_cast<RouteGroupPathNode*>(node);
            std::cout << "Route group " << route_group_path_node->getTopologyElement()->getId() << " = ";
            std::cout << route_group_path_node->getRemainingProcessingTime();
            std::cout << std::endl;
            auto next = route_group_path_node->getNext();
            if (next) {
                logRemainingProcessingTimesForPathNode(next, visited);
            }
            break;
    }

    case OPEN_GROUP_TOPOLOGY_ELEMENT: {
            auto open_group_path_node = dynamic_cast<OpenGroupPathNode*>(node);
            std::cout << "Open group " << open_group_path_node->getTopologyElement()->getId() << " = ";
            std::cout << open_group_path_node->getRemainingProcessingTime();
            std::cout << std::endl;
            for (auto [_, sub_path_node] : open_group_path_node->getSubPathNodes()) {
                logRemainingProcessingTimesForPathNode(sub_path_node, visited);
            }
            auto next = open_group_path_node->getNext();
            if (next) {
                logRemainingProcessingTimesForPathNode(next, visited);
            }
            break;
    }
    }
}
