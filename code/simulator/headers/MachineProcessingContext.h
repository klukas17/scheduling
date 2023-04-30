//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINEPROCESSINGCONTEXT_H
#define SCHEDULING_MACHINEPROCESSINGCONTEXT_H

#include "MachineNode.h"
#include "MachineBuffer.h"

class MachineProcessingContext {
private:
    MachineNode* machine;
    MachineBuffer* machine_buffer;
    long jobs_in_buffer;
    bool currently_working;
public:
    MachineProcessingContext(MachineNode* machine);
    void addJobToBuffer(long job_id);
    bool getCurrentlyWorking();
    long takeJobFromBuffer();
    MachineNode* getMachine();
    void decreaseJobsInBuffer();
    long getJobsInBuffer();
    void setCurrentlyWorking();
};


#endif //SCHEDULING_MACHINEPROCESSINGCONTEXT_H
