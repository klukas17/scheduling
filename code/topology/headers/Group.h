//
// Created by mihael on 01/05/23.
//

#ifndef SCHEDULING_GROUP_H
#define SCHEDULING_GROUP_H

#include "TopologyElement.h"
#include "vector"

class Group : public TopologyElement {
protected:
    std::vector<TopologyElement*> body;
public:
    explicit Group(long id);
    virtual ~Group() = 0;
    std::vector<TopologyElement*> getBody();
    void addElementToBody(TopologyElement* element);
};


#endif //SCHEDULING_GROUP_H
