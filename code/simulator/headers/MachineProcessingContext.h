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
    long steps_in_buffer;
    bool currently_working;
public:
    explicit MachineProcessingContext(GenotypeNode* node);
    GenotypeNode* getNode();
    void addStepToBuffer(long step_id, long job_id);
    std::pair<long, long> takeStepFromBuffer();
    [[nodiscard]] long getStepsInBuffer() const;
    void decreaseStepsInBuffer();
    [[nodiscard]] bool getCurrentlyWorking() const;
    void setCurrentlyWorking();
    void unsetCurrentlyWorking();
};


#endif //SCHEDULING_MACHINEPROCESSINGCONTEXT_H
