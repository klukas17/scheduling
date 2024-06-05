//
// Created by mihael on 6/1/24.
//

#include "GraphBasedGeneticProgrammingCreationOperator.h"

#include <climits>

#include "GBGPProgram.h"
#include "GraphBasedGeneticProgramming.h"
#include "UniformIntDistributionGenerator.h"

GraphBasedGeneticProgrammingCreationOperator::GraphBasedGeneticProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<GraphBasedGeneticProgrammingGenotypeBlueprint*>(genotype_blueprint);
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

GraphBasedGeneticProgrammingCreationOperator::~GraphBasedGeneticProgrammingCreationOperator() {
    delete generator;
}

Genotype* GraphBasedGeneticProgrammingCreationOperator::create() {

    std::map<int, GBGPNode*> nodes;
    std::map<int, double> constant_map;
    std::set<int> free_node_ids;
    auto inputs = blueprint->getInputs();
    std::map<int, std::set<int>> from_nodes;
    std::map<int, std::set<int>> to_nodes;
    int output_index;

    int inputs_size = inputs.size();
    for (int i = 0; i < blueprint->max_number_of_nodes; i++) {
        free_node_ids.insert(i + inputs_size);
    }

    auto number_of_nodes = generator->generate() % blueprint->max_number_of_nodes + 1;

    for (int i = 0; i < number_of_nodes; i++) {
        auto node_id = *free_node_ids.begin();
        free_node_ids.erase(node_id);
        auto node_type = blueprint->generateNodeType();
        if (node_type == GBGP_CONST) {
            constant_map[node_id] = blueprint->generateConstant();
        }
        int first_predecessor_index = generator->generate() % (inputs_size + nodes.size());
        int second_predecessor_index = generator->generate() % (inputs_size + nodes.size());
        int third_predecessor_index = generator->generate() % (inputs_size + nodes.size());

        from_nodes[node_id].insert(first_predecessor_index);
        from_nodes[node_id].insert(second_predecessor_index);
        from_nodes[node_id].insert(third_predecessor_index);

        to_nodes[first_predecessor_index].insert(node_id);
        to_nodes[second_predecessor_index].insert(node_id);
        to_nodes[third_predecessor_index].insert(node_id);

        nodes[node_id] = new GBGPNode(
            node_id,
            node_type,
            first_predecessor_index,
            second_predecessor_index,
            third_predecessor_index
        );
    }

    output_index = generator->generate() % (inputs_size + nodes.size());

    auto program = new GBGPProgram(
        nodes,
        constant_map,
        free_node_ids,
        inputs,
        from_nodes,
        to_nodes,
        output_index
    );
    auto gbgp = new GraphBasedGeneticProgramming(program);
    gbgp->setInputs(inputs);
    return gbgp;
}
