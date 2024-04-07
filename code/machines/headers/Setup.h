//
// Created by mihael on 9/19/23.
//

#ifndef SCHEDULING_SETUP_H
#define SCHEDULING_SETUP_H

#include "JobType.h"

class Setup {
    JobType* job_type_from;
    JobType* job_type_to;
    double duration;
public:
    Setup(JobType* job_type_from, JobType* job_type_to, double duration);
    [[nodiscard]] JobType* getJobTypeFrom() const;
    [[nodiscard]] JobType* getJobTypeTo() const;
    [[nodiscard]] double getDuration() const;
};

#endif //SCHEDULING_SETUP_H

