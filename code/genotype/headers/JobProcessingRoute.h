//
// Created by mihael on 07/05/23.
//

#ifndef SCHEDULING_JOBPROCESSINGROUTE_H
#define SCHEDULING_JOBPROCESSINGROUTE_H

#include "vector"
#include "map"
#include "JobProcessingStep.h"

class JobProcessingRoute {
    long job_id;
    std::vector<JobProcessingStep*> processing_steps;
    std::map<long, JobProcessingStep*> processing_steps_map;
    long current_index;
public:
    explicit JobProcessingRoute(long job_id);
    [[nodiscard]] long getJobId() const;
    void addProcessingStep(JobProcessingStep* processing_step);
    std::vector<JobProcessingStep*> getProcessingSteps();
    JobProcessingStep* getNextProcessingStep();
    JobProcessingStep* getProcessingStep(long step_id);
    [[nodiscard]] bool checkHasFinished() const;
    void resetCurrentIndex();
};

#endif //SCHEDULING_JOBPROCESSINGROUTE_H

