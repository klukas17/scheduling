//
// Created by mihael on 4/10/24.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "JobProcessingStep.h"

class Scheduler {
public:
    virtual double calculateScore(long machine_id, long job_id, long step_id) = 0;
    virtual bool comparePrioritiesOfTwoSteps(long machine_id, long step_id1, long step_id2) = 0;
    virtual JobProcessingStep* getNextProcessingStep(long job_id) = 0;
    virtual JobProcessingStep* getProcessingStep(long job_id, long step_id) = 0;
    virtual bool checkHasJobFinished(long job_id) = 0;
    virtual ~Scheduler();
};



#endif //SCHEDULER_H
