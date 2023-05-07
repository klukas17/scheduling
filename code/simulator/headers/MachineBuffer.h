//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINEBUFFER_H
#define SCHEDULING_MACHINEBUFFER_H

#include "MachineBufferElement.h"
#include "vector"
#include "map"
#include "tuple"

class MachineBuffer {
private:
    MachineBufferElement* head;
    std::map<long, long> step_index_to_processing_index;
    std::map<long, long> processing_index_to_step_index;
    std::map<long, MachineBufferElement*> step_index_to_node;
public:
    explicit MachineBuffer(std::vector<long> preferred_processing_order);
    void addStepToBuffer(long step_id, long job_id);
    std::pair<long, long> takeStepFromBuffer();
};


#endif //SCHEDULING_MACHINEBUFFER_H
