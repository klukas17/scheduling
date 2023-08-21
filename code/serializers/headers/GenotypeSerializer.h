//
// Created by mihael on 29/04/23.
//

/**
 * @file GenotypeSerializer.h
 * @brief Defines the GenotypeSerializer class for serializing individual genotypes.
 */

#ifndef SCHEDULING_GENOTYPESERIALIZER_H
#define SCHEDULING_GENOTYPESERIALIZER_H

#include "string"
#include "Individual.h"
#include <yaml-cpp/yaml.h>

/**
 * @class GenotypeSerializer
 * @brief Provides functionality to serialize individual genotypes.
 *
 * The GenotypeSerializer class offers static methods to serialize individual genotypes and their associated data
 * into YAML format. It helps create YAML representations of genotypes for storage or transfer.
 */
class GenotypeSerializer {
public:

    /**
     * @brief Serializes an individual's genotype and writes it to a YAML file.
     * @param path The path to the file where the genotype should be serialized.
     * @param individual A pointer to the Individual object whose genotype should be serialized.
     */
    static void serialize(const std::string& path, Individual* individual);

    /**
     * @brief Serializes the topology node of an individual's genotype and appends it to the YAML emitter.
     * @param individual A pointer to the Individual object whose genotype is being serialized.
     * @param out The YAML emitter used for writing YAML data.
     */
    static void serializeTopologyNode(Individual* individual, YAML::Emitter& out);

    /**
     * @brief Serializes the jobs node of an individual's genotype and appends it to the YAML emitter.
     * @param individual A pointer to the Individual object whose genotype is being serialized.
     * @param out The YAML emitter used for writing YAML data.
     */
    static void serializeJobsNode(Individual* individual, YAML::Emitter& out);

    /**
     * @brief Serializes a topology element node and appends it to the YAML emitter.
     * @param node A pointer to the GenotypeNode representing a topology element.
     * @param out The YAML emitter used for writing YAML data.
     */
    static void serializeTopologyElementNode(GenotypeNode* node, YAML::Emitter& out);
};

#endif //SCHEDULING_GENOTYPESERIALIZER_H
