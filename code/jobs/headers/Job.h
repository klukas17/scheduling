//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_JOB_H
#define SCHEDULING_JOB_H

#include "JobType.h"
#include "PathNode.h"
#include "map"
#include "vector"

class Job {
private:
    long id;
    JobType* job_type;
    PathNode* paths_root_node;
    long release_time;
    long due_time;
    long weight;
public:
    Job(long id, JobType* job_type, PathNode* paths_root_node, long release_time, long due_time, long weight);
    [[nodiscard]] long getId() const;
    JobType* getJobType();
    PathNode* getPathsRootNode();
    long getReleaseTime();
    long getDueTime();
    long getWeight();
};


#endif //SCHEDULING_JOB_H
