//
// Created by mihael on 01/05/23.
//

#ifndef SCHEDULING_PARALLELGROUP_H
#define SCHEDULING_PARALLELGROUP_H

#include "TopologyElement.h"
#include "vector"

class ParallelGroup : public TopologyElement {
private:
    std::vector<TopologyElement*> body;
public:
    explicit ParallelGroup(long id);
    std::vector<TopologyElement*> getBody();
    void addElementToBody(TopologyElement* element);
};


#endif //SCHEDULING_PARALLELGROUP_H
