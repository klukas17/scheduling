//
// Created by mihael on 29/04/23.
//

/**
 * @file Job.cpp
 * @brief Implements the member functions of the Job class.
 */

#include "Job.h"
#include "SchedulingError.h"
#include "GroupPathTreeNode.h"

Job::Job(long id, JobType* job_type, PathNode* paths_root_node, PathTreeNode* paths_root_tree_node, long release_time, long due_time, long weight) {
    this->id = id;
    this->job_type = job_type;
    this->paths_root_node = paths_root_node;
    this->paths_root_tree_node = paths_root_tree_node;
    this->release_time = release_time;
    this->due_time = due_time;
    this->weight = weight;
    indexPathTreeNodes(paths_root_tree_node);
}

long Job::getId() const {
    return id;
}

JobType *Job::getJobType() {
    return job_type;
}

std::map<long, long> Job::getProcessingTimes() {
    return processing_times;
}

long Job::getProcessingTime(long machine_id) {
    return processing_times[machine_id];
}

void Job::addProcessingTime(long machine_id, long time) {
    processing_times[machine_id] = time;
}

PathNode *Job::getPathsRootNode() {
    return paths_root_node;
}

PathTreeNode *Job::getPathsRootTreeNode() {
    return paths_root_tree_node;
}

PathTreeNode *Job::getPathTreeNode(long id) {
    return path_tree_node_map[id];
}

void Job::indexPathTreeNodes(PathTreeNode* node) {

    switch (node->getPathNode()->getTopologyElement()->getGeneralTopologyElementType()) {

        case ABSTRACT_GENERAL_TOPOLOGY_ELEMENT:
            throw SchedulingError("Abstract element encountered in Job::indexPathTreeNodes function.");

        case MACHINE_GENERAL_TOPOLOGY_ELEMENT:
            path_tree_node_map[node->getPathNode()->getPathNodeId()] = node;
            break;

        case GROUP_GENERAL_TOPOLOGY_ELEMENT:
            path_tree_node_map[node->getPathNode()->getPathNodeId()] = node;
            for (auto child_node : ((GroupPathTreeNode*)node)->getChildren()) {
                indexPathTreeNodes(child_node);
            }
            break;
    }
}

long Job::getReleaseTime() const {
    return release_time;
}

long Job::getDueTime() const {
    return due_time;
}

long Job::getWeight() const {
    return weight;
}