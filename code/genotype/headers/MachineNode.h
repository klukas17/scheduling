//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_MACHINENODE_H
#define SCHEDULING_MACHINENODE_H

#include "GenotypeNode.h"
#include "MachineType.h"

class MachineNode final : public GenotypeNode {
    MachineType* machine_type;
public:
    MachineNode(long id, MachineType* machine_type);
    [[nodiscard]] MachineType* getMachineType() const;
};

#endif //SCHEDULING_MACHINENODE_H

