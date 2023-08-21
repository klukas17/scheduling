//
// Created by mihael on 29/04/23.
//

/**
 * @file GenotypeDeserializer.h
 * @brief Defines the GenotypeDeserializer class for deserializing individual genotypes.
 */

#ifndef SCHEDULING_GENOTYPEDESERIALIZER_H
#define SCHEDULING_GENOTYPEDESERIALIZER_H

#include "Topology.h"
#include "Individual.h"
#include "Job.h"
#include "string"
#include "yaml-cpp/yaml.h"

/**
 * @class GenotypeDeserializer
 * @brief Provides functionality to deserialize individual genotypes from YAML data.
 *
 * The GenotypeDeserializer class offers static methods to deserialize individual genotypes and their associated data
 * from YAML format. It helps create Individual objects with genotypes based on deserialized YAML data.
 */
class GenotypeDeserializer {
public:
    /**
     * @brief Deserializes an individual's genotype from a YAML file and constructs an Individual object.
     * @param path The path to the YAML file containing the serialized genotype data.
     * @param topology A pointer to the Topology object used to map topology elements during deserialization.
     * @return A pointer to the constructed Individual object with the deserialized genotype.
     */
    static Individual* deserialize(const std::string& path, Topology* topology);

    /**
     * @brief Deserializes the topology node of an individual's genotype from a YAML node.
     * @param path The path to the YAML file containing the serialized genotype data.
     * @param node The YAML node representing the topology element.
     * @param genotype_node A pointer to the GenotypeNode that corresponds to the topology element.
     */
    static void deserializeTopologyNode(const std::string& path, const YAML::Node& node, GenotypeNode* genotype_node);

    /**
     * @brief Deserializes the jobs node of an individual's genotype from a YAML node and populates an Individual object.
     * @param path The path to the YAML file containing the serialized genotype data.
     * @param node The YAML node representing the jobs data.
     * @param individual A pointer to the Individual object to be populated with the deserialized genotype.
     */
    static void deserializeJobsNode(const std::string& path, const YAML::Node& node, Individual* individual);
};

#endif //SCHEDULING_GENOTYPEDESERIALIZER_H
