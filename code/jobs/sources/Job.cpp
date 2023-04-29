//
// Created by mihael on 29/04/23.
//

#include "Job.h"

Job::Job(long id, JobType *jobType) {
    this->id = id;
    this->jobType = jobType;
}