//
// Created by mihael on 29/04/23.
//

#include "Job.h"
#include "SchedulingError.h"
#include "GroupPathTreeNode.h"

Job::Job(long const id, JobType* job_type, PathNode* paths_root_node, PathTreeNode* paths_root_tree_node, double const release_time, double const due_time, double const weight) {
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

JobType *Job::getJobType() const {
    return job_type;
}

std::map<long, double> Job::getProcessingTimes() {
    return processing_times;
}

double Job::getProcessingTime(long const machine_id) {
    return processing_times[machine_id];
}

void Job::addProcessingTime(long const machine_id, double const time) {
    processing_times[machine_id] = time;
}

PathNode *Job::getPathsRootNode() const {
    return paths_root_node;
}

PathTreeNode *Job::getPathsRootTreeNode() const {
    return paths_root_tree_node;
}

PathTreeNode *Job::getPathTreeNode(long const id) {
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
            for (auto const child_node : dynamic_cast<GroupPathTreeNode*>(node)->getChildren()) {
                indexPathTreeNodes(child_node);
            }
            break;
    }
}

double Job::getReleaseTime() const {
    return release_time;
}

double Job::getDueTime() const {
    return due_time;
}

double Job::getWeight() const {
    return weight;
}