//
// Created by mihael on 2/11/24.
//

#ifndef JOBSTATISTICS_H
#define JOBSTATISTICS_H
#include "JobStatus.h"


class JobStatistics {
    long id;
    double release_time;
    double due_time;
    double weight;
    double exit_time;
    JobStatus job_status;
public:
    JobStatistics(long id, double release_time, double due_time, double weight);
    [[nodiscard]] long getId() const;
    [[nodiscard]] double getReleaseTime() const;
    [[nodiscard]] double getDueTime() const;
    [[nodiscard]] double getWeight() const;
    [[nodiscard]] double getExitTime() const;
    [[nodiscard]] JobStatus getJobStatus() const;
    void setExitTime(double exit_time);
    void setJobStatus(JobStatus job_status);
};



#endif //JOBSTATISTICS_H
