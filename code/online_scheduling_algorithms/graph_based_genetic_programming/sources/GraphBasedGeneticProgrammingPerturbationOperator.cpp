//
// Created by mihael on 6/1/24.
//

#include "GraphBasedGeneticProgrammingPerturbationOperator.h"

#include <climits>

#include "GraphBasedGeneticProgramming.h"
#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

GraphBasedGeneticProgrammingPerturbationOperator::GraphBasedGeneticProgrammingPerturbationOperator(
    GraphBasedGeneticProgrammingGenotypeBlueprint* blueprint,
    double perturbation_rate,
    int max_nodes_to_delete,
    int max_nodes_to_insert
) {
    this->blueprint = blueprint;
    this->perturbation_rate = perturbation_rate;
    this->max_nodes_to_delete = max_nodes_to_delete;
    this->max_nodes_to_insert = max_nodes_to_insert;
    this->chance_generator = new UniformRealDistributionGenerator(0, 1);
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
}

GraphBasedGeneticProgrammingPerturbationOperator::~GraphBasedGeneticProgrammingPerturbationOperator() {
    delete chance_generator;
    delete generator;
}

void GraphBasedGeneticProgrammingPerturbationOperator::perturbate(Genotype* genotype) {

    auto gbgp = dynamic_cast<GraphBasedGeneticProgramming*>(genotype);
    auto program = gbgp->getProgram();

    auto nodes_to_delete = generator->generate() % (max_nodes_to_delete + 1);
    for (int i = 0; i < nodes_to_delete && program->nodes.size() > 0; i++) {
        auto it = program->nodes.begin();
        std::advance(it, generator->generate() % program->nodes.size());
        auto [node_id, node] = *it;

        program->free_node_ids.insert(node_id);

        if (program->constant_map.contains(node_id)) {
            program->constant_map.erase(node_id);
        }

        for (auto to_node_id : program->from_nodes[node_id]) {
            program->to_nodes[to_node_id].erase(node_id);
        }

        for (auto from_node_id : program->to_nodes[node_id]) {
            auto from_node = program->nodes[from_node_id];

            if (from_node->first_predecessor_index == node_id) {
                from_node->first_predecessor_index = generator->generate() % from_node_id;
                while (program->free_node_ids.contains(from_node->first_predecessor_index)) {
                    from_node->first_predecessor_index--;
                }
                program->from_nodes[from_node_id].insert(from_node->first_predecessor_index);
                program->to_nodes[from_node->first_predecessor_index].insert(from_node_id);
            }

            if (from_node->second_predecessor_index == node_id) {
                from_node->second_predecessor_index = generator->generate() % from_node_id;
                while (program->free_node_ids.contains(from_node->second_predecessor_index)) {
                    from_node->second_predecessor_index--;
                }
                program->from_nodes[from_node_id].insert(from_node->second_predecessor_index);
                program->to_nodes[from_node->second_predecessor_index].insert(from_node_id);
            }

            if (from_node->third_predecessor_index == node_id) {
                from_node->third_predecessor_index = generator->generate() % from_node_id;
                while (program->free_node_ids.contains(from_node->third_predecessor_index)) {
                    from_node->third_predecessor_index--;
                }
                program->from_nodes[from_node_id].insert(from_node->third_predecessor_index);
                program->to_nodes[from_node->third_predecessor_index].insert(from_node_id);
            }

            program->from_nodes[from_node_id].erase(node_id);
        }

        program->from_nodes[node_id].clear();
        program->to_nodes[node_id].clear();

        if (program->output_node_id == node_id) {
            do {
               program->output_node_id = generator->generate() % (program->inputs.size() + blueprint->max_number_of_nodes);
            } while (program->free_node_ids.contains(program->output_node_id));
        }

        delete node;
        program->nodes.erase(node_id);
    }

    auto nodes_to_insert = generator->generate() % (max_nodes_to_insert + 1);
    for (int i = 0; i < nodes_to_insert && program->nodes.size() < blueprint->max_number_of_nodes; i++) {
        auto node_id = *program->free_node_ids.begin();
        program->free_node_ids.erase(node_id);
        auto node_type = blueprint->generateNodeType();
        if (node_type == GBGP_CONST) {
            program->constant_map[node_id] = blueprint->generateConstant();
        }
        int first_predecessor_index = generator->generate() % node_id;
        int second_predecessor_index = generator->generate() % node_id;
        int third_predecessor_index = generator->generate() % node_id;

        program->from_nodes[node_id].insert(first_predecessor_index);
        program->from_nodes[node_id].insert(second_predecessor_index);
        program->from_nodes[node_id].insert(third_predecessor_index);

        program->to_nodes[first_predecessor_index].insert(node_id);
        program->to_nodes[second_predecessor_index].insert(node_id);
        program->to_nodes[third_predecessor_index].insert(node_id);

        program->nodes[node_id] = new GBGPNode(
            node_id,
            node_type,
            first_predecessor_index,
            second_predecessor_index,
            third_predecessor_index
        );
    }

    auto changes = program->nodes.size() * perturbation_rate;
    for (int i = 0; i < changes; i++) {
        auto it = program->nodes.begin();
        std::advance(it, generator->generate() % program->nodes.size() + 1);

        if (it == program->nodes.end()) {
            do {
                program->output_node_id = generator->generate() % (program->inputs.size() + blueprint->max_number_of_nodes);
            } while (program->free_node_ids.contains(program->output_node_id));
            continue;
        }

        auto [node_id, node] = *it;

        auto random_number = generator->generate() % 4;

        if (random_number == 0) {
            if (node->node_type == GBGP_CONST) {
                program->constant_map.erase(node_id);
            }
            node->node_type = blueprint->generateNodeType();
            if (node->node_type == GBGP_CONST) {
                program->constant_map[node_id] = blueprint->generateConstant();
            }
        }

        else if (random_number == 1) {
            auto prev_first_predecessor_id = node->first_predecessor_index;
            auto next_first_predecessor_id = generator->generate() % node_id;
            while (program->free_node_ids.contains(next_first_predecessor_id)) {
                next_first_predecessor_id--;
            }
            if (node->second_predecessor_index != prev_first_predecessor_id && node->third_predecessor_index != prev_first_predecessor_id) {
                program->from_nodes[node_id].erase(prev_first_predecessor_id);
                program->to_nodes[prev_first_predecessor_id].erase(node_id);
            }
            node->first_predecessor_index = next_first_predecessor_id;
            program->from_nodes[node_id].insert(next_first_predecessor_id);
            program->to_nodes[next_first_predecessor_id].insert(node_id);
        }

        else if (random_number == 2) {
            auto prev_second_predecessor_id = node->first_predecessor_index;
            auto next_second_predecessor_id = generator->generate() % node_id;
            while (program->free_node_ids.contains(next_second_predecessor_id)) {
                next_second_predecessor_id--;
            }
            if (node->first_predecessor_index != prev_second_predecessor_id && node->third_predecessor_index != prev_second_predecessor_id) {
                program->from_nodes[node_id].erase(prev_second_predecessor_id);
                program->to_nodes[prev_second_predecessor_id].erase(node_id);
            }
            node->first_predecessor_index = next_second_predecessor_id;
            program->from_nodes[node_id].insert(next_second_predecessor_id);
            program->to_nodes[next_second_predecessor_id].insert(node_id);
        }

        else if (random_number == 3) {
            auto prev_third_predecessor_id = node->first_predecessor_index;
            auto next_third_predecessor_id = generator->generate() % node_id;
            while (program->free_node_ids.contains(next_third_predecessor_id)) {
                next_third_predecessor_id--;
            }
            if (node->first_predecessor_index != prev_third_predecessor_id && node->second_predecessor_index != prev_third_predecessor_id) {
                program->from_nodes[node_id].erase(prev_third_predecessor_id);
                program->to_nodes[prev_third_predecessor_id].erase(node_id);
            }
            node->first_predecessor_index = next_third_predecessor_id;
            program->from_nodes[node_id].insert(next_third_predecessor_id);
            program->to_nodes[next_third_predecessor_id].insert(node_id);
        }
    }
}

