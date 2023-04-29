//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINE_H
#define SCHEDULING_MACHINE_H

#include "TopologyElement.h"
#include "MachineType.h"

class Machine : public TopologyElement {
private:
    long id;
    MachineType* machine_type;
public:
    Machine(long id, MachineType* machine_type);
};


#endif //SCHEDULING_MACHINE_H
