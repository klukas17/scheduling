//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINEBUFFERELEMENT_H
#define SCHEDULING_MACHINEBUFFERELEMENT_H


class MachineBufferElement {
public:
    long step_id;
    long job_id;
    MachineBufferElement* prev;
    MachineBufferElement* next;
    MachineBufferElement(long step_id, long job_id);
};


#endif //SCHEDULING_MACHINEBUFFERELEMENT_H
