//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_SERIALGROUPNODE_H
#define SCHEDULING_SERIALGROUPNODE_H

#include "GroupNode.h"

class SerialGroupNode final : public GroupNode {
public:
    explicit SerialGroupNode(long id);
};

#endif //SCHEDULING_SERIALGROUPNODE_H
