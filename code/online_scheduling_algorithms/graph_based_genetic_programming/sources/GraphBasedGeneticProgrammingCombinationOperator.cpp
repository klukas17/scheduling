//
// Created by mihael on 6/1/24.
//

#include "GraphBasedGeneticProgrammingCombinationOperator.h"

#include <climits>
#include <queue>

#include "GraphBasedGeneticProgramming.h"
#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

GraphBasedGeneticProgrammingCombinationOperator::GraphBasedGeneticProgrammingCombinationOperator(
    GraphBasedGeneticProgrammingGenotypeBlueprint* blueprint,
    int max_number_of_nodes_to_crossover,
    double proceed_in_branch_chance
) {
    this->blueprint = blueprint;
    this->max_number_of_nodes_to_crossover = max_number_of_nodes_to_crossover;
    this->proceed_in_branch_chance = proceed_in_branch_chance;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
    this->chance_generator = new UniformRealDistributionGenerator(0, 1);
}

Genotype* GraphBasedGeneticProgrammingCombinationOperator::combine(Genotype* genotype1, Genotype* genotype2) {
    auto gbgp1 = dynamic_cast<GraphBasedGeneticProgramming*>(genotype1);
    auto gbgp2 = dynamic_cast<GraphBasedGeneticProgramming*>(genotype2);

    auto program2 = gbgp2->getProgram();

    auto gbgp = dynamic_cast<GraphBasedGeneticProgramming*>(gbgp1->copy());
    auto program1 = gbgp->getProgram();

    if (program1->nodes.empty() || program2->nodes.empty()) {
        return gbgp;
    }

    std::vector<GBGPNode*> nodes1, nodes2;
    std::queue<GBGPNode*> queue1, queue2;
    std::set<int> set1, set2;

    auto it1 = program1->nodes.begin();
    std::advance(it1, generator->generate() % program1->nodes.size());
    auto [_, root1] = *it1;
    nodes1.push_back(root1);
    queue1.push(root1);
    set1.insert(root1->node_id);

    while (!queue1.empty() && nodes1.size() < max_number_of_nodes_to_crossover) {
        auto n = queue1.front();
        queue1.pop();
        if (program1->nodes.contains(n->first_predecessor_index) && !set1.contains(n->first_predecessor_index) && chance_generator->generate() < proceed_in_branch_chance) {
            nodes1.push_back(program1->nodes[n->first_predecessor_index]);
            queue1.push(program1->nodes[n->first_predecessor_index]);
            set1.insert(program1->nodes[n->first_predecessor_index]->node_id);
        }
        if (nodes1.size() >= max_number_of_nodes_to_crossover) {
            break;
        }
        if (program1->nodes.contains(n->second_predecessor_index) && !set1.contains(n->second_predecessor_index) && chance_generator->generate() < proceed_in_branch_chance) {
            nodes1.push_back(program1->nodes[n->second_predecessor_index]);
            queue1.push(program1->nodes[n->second_predecessor_index]);
            set1.insert(program1->nodes[n->second_predecessor_index]->node_id);
        }
        if (nodes1.size() >= max_number_of_nodes_to_crossover) {
            break;
        }
        if (program1->nodes.contains(n->third_predecessor_index) && !set1.contains(n->third_predecessor_index) && chance_generator->generate() < proceed_in_branch_chance) {
            nodes1.push_back(program1->nodes[n->third_predecessor_index]);
            queue1.push(program1->nodes[n->third_predecessor_index]);
            set1.insert(program1->nodes[n->third_predecessor_index]->node_id);
        }
        if (nodes1.size() >= max_number_of_nodes_to_crossover) {
            break;
        }
    }

    auto it2 = program2->nodes.begin();
    std::advance(it2, generator->generate() % program2->nodes.size());
    auto [__, root2] = *it2;
    nodes2.push_back(root2);
    queue2.push(root2);
    set2.insert(root2->node_id);

    int max_nodes_to_crossover = nodes1.size();
    while (!queue2.empty() && nodes2.size() < max_nodes_to_crossover) {
        auto n = queue2.front();
        queue2.pop();
        if (program2->nodes.contains(n->first_predecessor_index) && !set2.contains(n->first_predecessor_index) && chance_generator->generate() < proceed_in_branch_chance) {
            nodes2.push_back(program2->nodes[n->first_predecessor_index]);
            queue2.push(program2->nodes[n->first_predecessor_index]);
            set2.insert(program2->nodes[n->first_predecessor_index]->node_id);
        }
        if (nodes2.size() >= max_nodes_to_crossover) {
            break;
        }
        if (program2->nodes.contains(n->second_predecessor_index) && !set2.contains(n->second_predecessor_index) && chance_generator->generate() < proceed_in_branch_chance) {
            nodes2.push_back(program2->nodes[n->second_predecessor_index]);
            queue2.push(program2->nodes[n->second_predecessor_index]);
            set2.insert(program2->nodes[n->second_predecessor_index]->node_id);
        }
        if (nodes2.size() >= max_nodes_to_crossover) {
            break;
        }
        if (program2->nodes.contains(n->third_predecessor_index) && !set2.contains(n->third_predecessor_index) && chance_generator->generate() < proceed_in_branch_chance) {
            nodes2.push_back(program2->nodes[n->third_predecessor_index]);
            queue2.push(program2->nodes[n->third_predecessor_index]);
            set2.insert(program2->nodes[n->third_predecessor_index]->node_id);
        }
        if (nodes2.size() >= max_nodes_to_crossover) {
            break;
        }
    }

    while (nodes2.size() > nodes1.size()) {
        nodes2.pop_back();
    }

    while (nodes1.size() > nodes2.size()) {
        nodes1.pop_back();
    }

    auto comp = [](GBGPNode* a, GBGPNode* b) {
        return a->node_id < b->node_id;
    };

    std::sort(nodes1.begin(), nodes1.end(), comp);
    std::sort(nodes2.begin(), nodes2.end(), comp);

    std::map<int, int> nodes2_to_nodes1, nodes1_to_nodes2;
    for (int i = 0; i < nodes1.size(); i++) {
        nodes1_to_nodes2[nodes1[i]->node_id] = nodes2[i]->node_id;
        nodes2_to_nodes1[nodes2[i]->node_id] = nodes1[i]->node_id;
    }

    for (int i = 0; i < nodes1.size(); i++) {
        auto node = nodes1[i];
        if (node->node_type == GBGP_CONST) {
            program1->constant_map.erase(node->node_id);
        }
        node->node_type = nodes2[i]->node_type;
        if (node->node_type == GBGP_CONST) {
            program1->constant_map[node->node_id] = program2->constant_map[node->node_id];
        }
    }

    for (int i = 0; i < nodes2.size(); i++) {
        auto node2 = nodes2[i];
        auto first_predecessor_id = node2->first_predecessor_index;
        auto second_predecessor_id = node2->second_predecessor_index;
        auto third_predecessor_id = node2->third_predecessor_index;

        auto node1 = program1->nodes[nodes2_to_nodes1[node2->node_id]];
        auto node_id = node1->node_id;

        if (set2.contains(first_predecessor_id)) {
            auto next_predecessor_id = program1->nodes[nodes2_to_nodes1[first_predecessor_id]]->node_id;
            auto prev_predecessor_id = node1->first_predecessor_index;

            if (node1->second_predecessor_index != prev_predecessor_id && node1->third_predecessor_index != prev_predecessor_id) {
                program1->from_nodes[node_id].erase(prev_predecessor_id);
                program1->to_nodes[prev_predecessor_id].erase(node_id);
            }
            node1->first_predecessor_index = next_predecessor_id;
            program1->from_nodes[node_id].insert(next_predecessor_id);
            program1->to_nodes[next_predecessor_id].insert(node_id);
        }

        if (set2.contains(second_predecessor_id)) {
            auto next_predecessor_id = program1->nodes[nodes2_to_nodes1[second_predecessor_id]]->node_id;
            auto prev_predecessor_id = node1->second_predecessor_index;

            if (node1->first_predecessor_index != prev_predecessor_id && node1->third_predecessor_index != prev_predecessor_id) {
                program1->from_nodes[node_id].erase(prev_predecessor_id);
                program1->to_nodes[prev_predecessor_id].erase(node_id);
            }
            node1->second_predecessor_index = next_predecessor_id;
            program1->from_nodes[node_id].insert(next_predecessor_id);
            program1->to_nodes[next_predecessor_id].insert(node_id);
        }

        if (set2.contains(third_predecessor_id)) {
            auto next_predecessor_id = program1->nodes[nodes2_to_nodes1[third_predecessor_id]]->node_id;
            auto prev_predecessor_id = node1->third_predecessor_index;

            if (node1->first_predecessor_index != prev_predecessor_id && node1->second_predecessor_index != prev_predecessor_id) {
                program1->from_nodes[node_id].erase(prev_predecessor_id);
                program1->to_nodes[prev_predecessor_id].erase(node_id);
            }
            node1->third_predecessor_index = next_predecessor_id;
            program1->from_nodes[node_id].insert(next_predecessor_id);
            program1->to_nodes[next_predecessor_id].insert(node_id);
        }
    }

    return gbgp;
}
