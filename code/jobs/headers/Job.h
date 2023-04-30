//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_JOB_H
#define SCHEDULING_JOB_H

#include "JobType.h"
#include "map"
#include "vector"

class Job {
private:
    long id;
    JobType* job_type;
    std::vector<long> processing_route;
    std::map<long, long> processing_times;
public:
    Job(long id, JobType* job_type);
    long getId();
    void addMachineToProcessingRoute(long machine_id);
    void setProcessingTime(long machine_id, long processing_time);
    long getProcessingTime(long machine_id);
};


#endif //SCHEDULING_JOB_H
