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

JobProcessingContext::JobProcessingContext(Job* job) {
    this->job = job;
    this->path_node = job->getPathsRootNode();
    this->job_processing_step = nullptr;
    this->last_processed_path_node_id = -1;
    this->processing_started = false;
    this->previous_machine_processing_context = nullptr;
}

Job *JobProcessingContext::getJob() const {
    return job;
}

PathNode *JobProcessingContext::getPathNode() const {
    return path_node;
}

void JobProcessingContext::setJobProcessingStep(JobProcessingStep *job_processing_step) {
    this->job_processing_step = job_processing_step;
}

void JobProcessingContext::moveToNextPathNode(long const next_machine_id) {

    if (!path_node || job_processing_step->getMachineId() != next_machine_id) {
        throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
    }

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