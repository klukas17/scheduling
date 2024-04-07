//
// Created by mihael on 9/16/23.
//

#ifndef SCHEDULING_JOBPROCESSINGPREREQUISITES_H
#define SCHEDULING_JOBPROCESSINGPREREQUISITES_H

#include "vector"
#include "Prerequisite.h"

class JobProcessingPrerequisites {
    long job_id;
    long machine_id;
    long step_id;
    std::vector<Prerequisite*> prerequisites;
    std::vector<bool> prerequisites_satisfied;
public:
    JobProcessingPrerequisites(long job_id, long machine_id, long step_id, const std::vector<Prerequisite*>& prerequisites);
    [[nodiscard]] long getJobId() const;
    [[nodiscard]] long getMachineId() const;
    [[nodiscard]] long getStepId() const;
    void updatePrerequisites(long machine_id, long job_id, long repetitions);
    bool checkAllPrerequisitesSatisfied();
};

#endif //SCHEDULING_JOBPROCESSINGPREREQUISITES_H
