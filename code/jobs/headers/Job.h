//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_JOB_H
#define SCHEDULING_JOB_H

#include "JobType.h"

class Job {
private:
    long id;
    JobType* jobType;
public:
    Job(long id, JobType* jobType);
};


#endif //SCHEDULING_JOB_H
