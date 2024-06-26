//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINEBUFFERELEMENT_H
#define SCHEDULING_MACHINEBUFFERELEMENT_H

class MachineBufferElement {
public:
    long step_id;
    long job_id;
    long job_type_id;
    double time_start_processing;
    double time_remaining_processing;
    bool preempt;
    double score;
    MachineBufferElement(long step_id, long job_id, long job_type_id, double time_start_processing, double time_remaining_processing, bool preempt, double score);
};

#endif //SCHEDULING_MACHINEBUFFERELEMENT_H
