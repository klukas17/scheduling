//
// Created by mihael on 07/05/23.
//

#ifndef SCHEDULING_JOBPROCESSINGSTEP_H
#define SCHEDULING_JOBPROCESSINGSTEP_H


class JobProcessingStep {
private:
    long processing_step_id;
    long machine_id;
public:
    JobProcessingStep(long processing_step_id, long machine_id);
    [[nodiscard]] long getProcessingStepId() const;
    [[nodiscard]] long getMachineId() const;
};


#endif //SCHEDULING_JOBPROCESSINGSTEP_H
