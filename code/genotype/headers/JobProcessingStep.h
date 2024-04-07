//
// Created by mihael on 07/05/23.
//

#ifndef SCHEDULING_JOBPROCESSINGSTEP_H
#define SCHEDULING_JOBPROCESSINGSTEP_H

class JobProcessingStep {
    long processing_step_id;
    long machine_id;
    long job_id;
    long path_node_id;

public:
    JobProcessingStep(long processing_step_id, long machine_id, long job_id, long path_node_id);
    [[nodiscard]] long getProcessingStepId() const;
    [[nodiscard]] long getMachineId() const;
    [[nodiscard]] long getJobId() const;
    [[nodiscard]] long getPathNodeId() const;
};

#endif //SCHEDULING_JOBPROCESSINGSTEP_H
