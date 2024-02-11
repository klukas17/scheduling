//
// Created by mihael on 2/11/24.
//

#ifndef JOBSTATISTICS_H
#define JOBSTATISTICS_H
#include "JobStatus.h"


class JobStatistics {
private:
    long id;
    long release_time;
    long due_time;
    long weight;
    long exit_time;
    JobStatus job_status;
public:
    JobStatistics(long id, long release_time, long due_time, long weight);
    long getId();
    long getReleaseTime();
    long getDueTime();
    long getWeight();
    long getExitTime();
    JobStatus getJobStatus();
    void setExitTime(long exit_time);
    void setJobStatus(JobStatus job_status);
};



#endif //JOBSTATISTICS_H
