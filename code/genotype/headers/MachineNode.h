//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINENODE_H
#define SCHEDULING_MACHINENODE_H

#include "GenotypeNode.h"
#include "MachineType.h"
#include "vector"

class MachineNode : public GenotypeNode {
private:
    MachineType* machine_type;
public:
    MachineNode(long id, MachineType* machine_type);
    MachineType* getMachineType();
};


#endif //SCHEDULING_MACHINENODE_H
