//
// Created by mihael on 07/05/23.
//

#ifndef SCHEDULING_JOBPROCESSINGROUTE_H
#define SCHEDULING_JOBPROCESSINGROUTE_H

#include "vector"
#include "JobProcessingStep.h"

class JobProcessingRoute {
private:
    long job_id;
    std::vector<JobProcessingStep*> processing_steps;
    long step_count;
public:
    explicit JobProcessingRoute(long job_id);
    [[nodiscard]] long getJobId() const;
    void addProcessingStep(JobProcessingStep* processing_step);
    std::vector<JobProcessingStep*> getProcessingSteps();
    JobProcessingStep* getProcessingStep(long index);
    [[nodiscard]] long getStepCount() const;
};


#endif //SCHEDULING_JOBPROCESSINGROUTE_H
