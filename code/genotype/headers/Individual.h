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
    GenotypeNode* root_node;
    std::map<long, GenotypeNode*> genotype_node_map;
    std::map<long, JobProcessingRoute*> processing_routes;
public:
    explicit Individual(const Topology* topology);
    static GenotypeNode* createNode(TopologyElement* topology_element);
    [[nodiscard]] GenotypeNode* getRootNode() const;
    std::map<long, GenotypeNode*> getGenotypeNodeMap();
    void mapGenotypeNodes(GenotypeNode* node);
    JobProcessingRoute* getProcessingRoute(long job_id);
    std::map<long, JobProcessingRoute*> getProcessingRoutes();
    void setProcessingRoute(long job_id, JobProcessingRoute* job_processing_route);
};

#endif //SCHEDULING_INDIVIDUAL_H
