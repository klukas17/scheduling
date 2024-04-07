//
// Created by mihael on 01/05/23.
//

#ifndef SCHEDULING_GROUP_H
#define SCHEDULING_GROUP_H

#include "TopologyElement.h"
#include <vector>

class Group : public TopologyElement {
protected:
    std::vector<TopologyElement*> children;

public:
    explicit Group(long id);
    ~Group() override = 0;
    std::vector<TopologyElement*> getChildren();
    void addChild(TopologyElement* child);
};

#endif //SCHEDULING_GROUP_H
