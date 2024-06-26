//
// Created by mihael on 8/13/23.
//

#ifndef SCHEDULING_JOBTYPEMAP_H
#define SCHEDULING_JOBTYPEMAP_H

#include "JobType.h"

class JobTypeMap {
    std::map<long, JobType*> job_type_map;
public:
    JobTypeMap();
    std::map<long, JobType*> getJobTypeMap();
    JobType* getJobType(long job_type_id);
    void addJobType(long job_type_id, JobType* job_type);
    std::map<long, std::tuple<PathNode*, PathTreeNode*, std::set<long>>> prepareDataForJobSequenceGenerator(TopologyElement* topology_element);
};

#endif // SCHEDULING_JOBTYPEMAP_H

