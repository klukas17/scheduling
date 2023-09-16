//
// Created by mihael on 9/2/23.
//

/**
 * @file JobProcessingContext.cpp
 * @brief Implements the member functions of the JobProcessingContext class.
 */

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
}

Job *JobProcessingContext::getJob() {
    return job;
}

PathNode *JobProcessingContext::getPathNode() {
    return path_node;
}

void JobProcessingContext::setJobProcessingStep(JobProcessingStep *job_processing_step) {
    this->job_processing_step = job_processing_step;
}

void JobProcessingContext::moveToNextPathNode(long next_machine_id) {

    if (!path_node || job_processing_step->getMachineId() != next_machine_id) {
        throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
    }

    if (processing_started && path_node->getTopologyElement()->getTopologyElementType() == PARALLEL_GROUP_TOPOLOGY_ELEMENT && last_processed_path_node_id == path_node->getPathNodeId()) {
        auto parallel_group_path_node = (ParallelGroupPathNode*) path_node;
        PathNode* next_path_node = nullptr;
        for (auto candidate_next : parallel_group_path_node->getNext()) {
            if (candidate_next.first == next_machine_id) {
                next_path_node = candidate_next.second;
                break;
            }
        }
        if (!next_path_node) {
            throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
        }
        path_node = next_path_node;
    }

    if (processing_started && path_node->getTopologyElement()->getTopologyElementType() == OPEN_GROUP_TOPOLOGY_ELEMENT && last_processed_path_node_id == path_node->getPathNodeId() && !frames.empty() && frames.top()->getOpenGroupPathTreeNode()->getPathNode()->getPathNodeId() == path_node->getPathNodeId()) {
        auto open_group_path_node = (OpenGroupPathNode*) path_node;
        PathNode* next_path_node = nullptr;
        for (auto candidate_sub_path_node : ((OpenGroupPathTreeNode*) job->getPathTreeNode(path_node->getPathNodeId()))->getChildren()) {
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
            auto machine_path_node = (MachinePathNode*) path_node;
            if (path_node->getTopologyElement()->getId() != next_machine_id) {
                throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
            }
            path_node = machine_path_node->getNext();
            break;
        }

        case SERIAL_GROUP_TOPOLOGY_ELEMENT: {
            auto serial_group_path_node = (SerialGroupPathNode*) path_node;
            if (path_node->getTopologyElement()->getId() != next_machine_id) {
                throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
            }
            path_node = serial_group_path_node->getNext();
            break;
        }

        case PARALLEL_GROUP_TOPOLOGY_ELEMENT: {
            auto parallel_group_path_node = (ParallelGroupPathNode*) path_node;
            if (path_node->getTopologyElement()->getId() != next_machine_id) {
                throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
            }
            break;
        }

        case ROUTE_GROUP_TOPOLOGY_ELEMENT: {
            auto route_group_path_node = (RouteGroupPathNode*) path_node;
            if (path_node->getTopologyElement()->getId() != next_machine_id) {
                throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
            }
            path_node = route_group_path_node->getNext();
            break;
        }

        case OPEN_GROUP_TOPOLOGY_ELEMENT: {
            auto open_group_path_node = (OpenGroupPathNode*) path_node;
            if (path_node->getTopologyElement()->getId() != next_machine_id) {
                throw SchedulingError("Path invalid for job " + std::to_string(job->getId()));
            }
            if (open_group_path_node->getSubPathNodes().empty()) {
                path_node = open_group_path_node->getNext();
            }
            else {
                auto frame = new JobProcessingContextFrame((OpenGroupPathTreeNode*)job->getPathTreeNode(open_group_path_node->getPathNodeId()));
                frames.push(frame);
            }
            break;
        }
    }

    while (!path_node && !frames.empty()) {
        path_node = frames.top()->getOpenGroupPathTreeNode()->getPathNode();
        last_processed_path_node_id = path_node->getPathNodeId();
        if (frames.top()->checkAllChildrenVisited()) {
            auto frame = frames.top();
            frames.pop();
            delete frame;
            path_node = ((OpenGroupPathNode*) path_node)->getNext();
        }
    }
}

bool JobProcessingContext::checkIfPathFinished() {
    return !path_node && !job_processing_step && frames.empty();
}