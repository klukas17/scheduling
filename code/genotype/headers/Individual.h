//
// Created by mihael on 29/04/23.
//

#ifndef SCHEDULING_INDIVIDUAL_H
#define SCHEDULING_INDIVIDUAL_H

#include "Topology.h"
#include "GenotypeNode.h"
#include "JobProcessingRoute.h"
#include "map"

class Individual {
private:
    GenotypeNode* root_node;
    std::map<long, JobProcessingRoute*> processing_routes;
public:
    explicit Individual(Topology* topology);
    static GenotypeNode* createNode(TopologyElement* topology_element);
    GenotypeNode* getRootNode();
    JobProcessingRoute* getProcessingRoute(long job_id);
    std::map<long, JobProcessingRoute*> getProcessingRoutes();
    void setProcessingRoute(long job_id, JobProcessingRoute* job_processing_route);
};


#endif //SCHEDULING_INDIVIDUAL_H
