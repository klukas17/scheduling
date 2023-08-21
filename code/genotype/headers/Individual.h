//
// Created by mihael on 29/04/23.
//

/**
 * @file Individual.h
 * @brief Defines the Individual class for representing an individual (a schedule) in the scheduling optimization.
 */

#ifndef SCHEDULING_INDIVIDUAL_H
#define SCHEDULING_INDIVIDUAL_H

#include "Topology.h"
#include "GenotypeNode.h"
#include "JobProcessingRoute.h"
#include "map"

/**
 * @class Individual
 * @brief Represents an individual in the scheduling optimization.
 *
 * The Individual class encapsulates information about an individual in the scheduling optimization process.
 * It includes attributes to store the root genotype node, processing routes for jobs, and methods for managing and accessing this information.
 */
class Individual {
private:
    GenotypeNode* root_node; /**< Pointer to the root genotype node of the individual. */
    std::map<long, JobProcessingRoute*> processing_routes; /**< Map of job IDs to their associated processing routes. */
public:
    /**
     * @brief Constructs an Individual object for the provided topology.
     * @param topology A pointer to the topology used for creating the individual.
     */
    explicit Individual(Topology* topology);

    /**
     * @brief Creates a genotype node based on the provided topology element.
     * @param topology_element A pointer to the topology element for which to create a genotype node.
     * @return A pointer to the created genotype node.
     */
    static GenotypeNode* createNode(TopologyElement* topology_element);

    /**
     * @brief Retrieves the root genotype node of the individual.
     * @return A pointer to the root genotype node.
     */
    GenotypeNode* getRootNode();

    /**
     * @brief Retrieves the processing route for a specific job.
     * @param job_id The identifier of the job for which to retrieve the processing route.
     * @return A pointer to the associated JobProcessingRoute object.
     */
    JobProcessingRoute* getProcessingRoute(long job_id);

    /**
     * @brief Retrieves the map of job IDs to their associated processing routes.
     * @return A map containing job IDs as keys and pointers to JobProcessingRoute objects as values.
     */
    std::map<long, JobProcessingRoute*> getProcessingRoutes();

    /**
     * @brief Sets the processing route for a specific job.
     * @param job_id The identifier of the job for which to set the processing route.
     * @param job_processing_route A pointer to the JobProcessingRoute object representing the processing route.
     */
    void setProcessingRoute(long job_id, JobProcessingRoute* job_processing_route);
};

#endif //SCHEDULING_INDIVIDUAL_H
