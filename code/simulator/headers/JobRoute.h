//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_JOBROUTE_H
#define SCHEDULING_JOBROUTE_H

#include "vector"
#include "Individual.h"
#include "Job.h"
#include "JobProcessingRoute.h"

class JobRoute {
private:
    Job* job;
    JobProcessingRoute* job_processing_route;
    long current_index;
public:
    JobRoute(Job *job, JobProcessingRoute* job_processing_route);
    JobProcessingRoute* getProcessingRoute();
    JobProcessingStep* getNextProcessingStep();
    [[nodiscard]] long getCurrentIndex() const;
    bool checkHasFinished();
};


#endif //SCHEDULING_JOBROUTE_H
