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
    MachineType* machineType;
public:
    Machine(long id, MachineType* machineType);
};


#endif //SCHEDULING_MACHINE_H
