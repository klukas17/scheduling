//
// Created by mihael on 29/04/23.
//

#include "Job.h"

Job::Job(long id, JobType *job_type) {
    this->id = id;
    this->job_type = job_type;
}