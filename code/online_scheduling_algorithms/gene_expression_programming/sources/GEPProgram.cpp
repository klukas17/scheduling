//
// Created by mihael on 5/30/24.
//

#include "GEPProgram.h"

#include <queue>
#include <utility>

GEPProgram::GEPProgram(
    std::vector<GEPGenotypeNode*> genotype_nodes,
    std::map<int, double> constant_map,
    std::map<int, std::string> param_map
) {
    this->genotype_nodes = std::move(genotype_nodes);;
    this->constant_map = std::move(constant_map);
    this->param_map = std::move(param_map);
    this->phenotype_root_node = nullptr;
    buildPhenotype();
}

GEPProgram::~GEPProgram() {
    for (auto & i : genotype_nodes) {
        delete i;
    }
    delete phenotype_root_node;
}

GEPProgram* GEPProgram::copy() {
    std::vector<GEPGenotypeNode*> nodes_copy;
    nodes_copy.reserve(genotype_nodes.size());
    for (auto node : genotype_nodes) {
        nodes_copy.push_back(node->copy());
    }
    return new GEPProgram(nodes_copy, constant_map, param_map);
}

void GEPProgram::buildPhenotype() {

    if (phenotype_root_node != nullptr) {
        delete phenotype_root_node;
        phenotype_root_node = nullptr;
    }

    std::queue<GEPPhenotypeNode*> queue;

    auto genotype_root_node = genotype_nodes[0];
    phenotype_root_node = new GEPPhenotypeNode(genotype_root_node->node_id, genotype_root_node->node_type, constant_map, param_map);
    queue.push(phenotype_root_node);

    int index = 1;

    while (!queue.empty()) {
        auto node = queue.front();
        queue.pop();

        switch(node->node_type) {

        case GEP_CONST:
        case GEP_PARAM:
            {
                break;
            }

        case GEP_UNARY_MINUS:
        case GEP_SQUARE:
        case GEP_ROOT:
            {
                auto first_child = new GEPPhenotypeNode(index, genotype_nodes[index]->node_type, constant_map, param_map);
                index++;
                node->children.push_back(first_child);
                queue.push(first_child);
                break;
            }

        case GEP_PLUS:
        case GEP_MINUS:
        case GEP_TIMES:
        case GEP_DIVIDE:
            {
                auto first_child = new GEPPhenotypeNode(index, genotype_nodes[index]->node_type, constant_map, param_map);
                index++;
                node->children.push_back(first_child);
                queue.push(first_child);

                auto second_child = new GEPPhenotypeNode(index, genotype_nodes[index]->node_type, constant_map, param_map);
                index++;
                node->children.push_back(second_child);
                queue.push(second_child);

                break;
            }

        case GEP_BRANCH:
            {
                auto first_child = new GEPPhenotypeNode(index, genotype_nodes[index]->node_type, constant_map, param_map);
                index++;
                node->children.push_back(first_child);
                queue.push(first_child);

                auto second_child = new GEPPhenotypeNode(index, genotype_nodes[index]->node_type, constant_map, param_map);
                index++;
                node->children.push_back(second_child);
                queue.push(second_child);

                auto third_child = new GEPPhenotypeNode(index, genotype_nodes[index]->node_type, constant_map, param_map);
                index++;
                node->children.push_back(third_child);
                queue.push(third_child);

                break;
            }
        }
    }
}

double GEPProgram::executeProgram(std::map<std::string, double> params) {
    return phenotype_root_node->eval(params);
}

