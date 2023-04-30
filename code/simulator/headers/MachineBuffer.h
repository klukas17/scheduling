//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINEBUFFER_H
#define SCHEDULING_MACHINEBUFFER_H

#include "MachineBufferElement.h"
#include "vector"
#include "map"

class MachineBuffer {
private:
    MachineBufferElement* head;
    std::map<long, long> job_index_to_processing_index;
    std::map<long, long> processing_index_to_job_index;
    std::map<long, MachineBufferElement*> job_index_to_node;
public:
    explicit MachineBuffer(std::vector<long> preferred_processing_order);
    void addJobToBuffer(long job_id);
    long takeJobFromBuffer();
};


#endif //SCHEDULING_MACHINEBUFFER_H
