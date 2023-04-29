//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_JOB_H
#define SCHEDULING_JOB_H

#include "JobType.h"

class Job {
private:
    long id;
    JobType* job_type;
public:
    Job(long id, JobType* job_type);
};


#endif //SCHEDULING_JOB_H
