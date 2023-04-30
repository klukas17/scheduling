//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINEPROCESSINGCONTEXT_H
#define SCHEDULING_MACHINEPROCESSINGCONTEXT_H

#include "GenotypeNode.h"
#include "MachineBuffer.h"

class MachineProcessingContext {
private:
    GenotypeNode* node;
    MachineBuffer* machine_buffer;
    long jobs_in_buffer;
    bool currently_working;
public:
    explicit MachineProcessingContext(GenotypeNode* node);
    GenotypeNode* getNode();
    void addJobToBuffer(long job_id);
    long takeJobFromBuffer();
    [[nodiscard]] long getJobsInBuffer() const;
    void decreaseJobsInBuffer();
    [[nodiscard]] bool getCurrentlyWorking() const;
    void setCurrentlyWorking();
    void unsetCurrentlyWorking();
};


#endif //SCHEDULING_MACHINEPROCESSINGCONTEXT_H
