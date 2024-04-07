//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_JOB_H
#define SCHEDULING_JOB_H

#include "JobType.h"
#include "PathNode.h"
#include "PathTreeNode.h"
#include "map"

class Job {
    long id;
    JobType* job_type;
    std::map<long, double> processing_times;
    PathNode* paths_root_node;
    PathTreeNode* paths_root_tree_node;
    std::map<long, PathTreeNode*> path_tree_node_map;
    double release_time;
    double due_time;
    double weight;
public:
    Job(long id, JobType* job_type, PathNode* paths_root_node, PathTreeNode* paths_root_tree_node, double release_time, double due_time, double weight);
    [[nodiscard]] long getId() const;
    [[nodiscard]] JobType* getJobType() const;
    std::map<long, double> getProcessingTimes();
    double getProcessingTime(long machine_id);
    void addProcessingTime(long machine_id, double time);
    [[nodiscard]] PathNode* getPathsRootNode() const;
    [[nodiscard]] PathTreeNode* getPathsRootTreeNode() const;
    PathTreeNode* getPathTreeNode(long id);
    void indexPathTreeNodes(PathTreeNode* node);
    [[nodiscard]] double getReleaseTime() const;
    [[nodiscard]] double getDueTime() const;
    [[nodiscard]] double getWeight() const;
};

#endif //SCHEDULING_JOB_H
