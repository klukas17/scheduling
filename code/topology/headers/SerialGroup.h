//
// Created by mihael on 30/04/23.
//

#ifndef SCHEDULING_SERIALGROUP_H
#define SCHEDULING_SERIALGROUP_H

#include "TopologyElement.h"
#include "vector"

class SerialGroup : public TopologyElement {
private:
    std::vector<TopologyElement*> body;
public:
    explicit SerialGroup(long id);
    std::vector<TopologyElement*> getBody();
    void addElementToBody(TopologyElement* element);
};


#endif //SCHEDULING_SERIALGROUP_H
