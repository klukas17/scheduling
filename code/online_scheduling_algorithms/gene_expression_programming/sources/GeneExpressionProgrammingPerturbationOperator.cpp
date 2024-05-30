//
// Created by mihael on 5/29/24.
//

#include "GeneExpressionProgrammingPerturbationOperator.h"
#include <climits>

#include "GeneExpressionProgramming.h"
#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

GeneExpressionProgrammingPerturbationOperator::GeneExpressionProgrammingPerturbationOperator(
    GeneExpressionProgrammingGenotypeBlueprint* blueprint,
    double perturbation_rate,
    double chance_of_transposition,
    int transposition_max_length
) {
    this->blueprint = blueprint;
    this->perturbation_rate = perturbation_rate;
    this->chance_of_transposition = chance_of_transposition;
    this->transposition_max_length = transposition_max_length;
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);
    this->transposition_chance_generator = new UniformRealDistributionGenerator(0, 1);
}

void GeneExpressionProgrammingPerturbationOperator::perturbate(Genotype* genotype) {
    auto gep = dynamic_cast<GeneExpressionProgramming*>(genotype);
    auto program = gep->getProgram();
    auto number_of_nodes = blueprint->head_size + blueprint->tail_size;
    auto changes = number_of_nodes * perturbation_rate;

    for (int i = 0; i < changes; i++) {
        auto node_index = generator->generate() % number_of_nodes;
        auto node = program->genotype_nodes[node_index];

        if (node->node_type == GEP_CONST) {
            program->constant_map.erase(node_index);
        }
        if (node->node_type == GEP_PARAM) {
            program->param_map.erase(node_index);
        }

        auto node_type = node_index < blueprint->head_size ? blueprint->generateNodeTypeForHead() : blueprint->generateNodeTypeForTail();
        node->node_type = node_type;

        if (node_type == GEP_CONST) {
            program->constant_map[node_index] = blueprint->generateConstant();
        }
        if (node_type == GEP_PARAM) {
            program->param_map[node_index] = blueprint->generateParam(gep->getInputs());
        }
    }

    if (transposition_chance_generator->generate() < this->chance_of_transposition) {
        //
        // auto transposition_start_index = generator->generate() % number_of_nodes;
        // auto transposition_length = generator->generate() % transposition_max_length + 1;
        // auto transposition_end_index = transposition_start_index + transposition_length;
        //
        // if (transposition_start_index < blueprint->head_size) {
        //     transposition_end_index = std::min(transposition_end_index, blueprint->head_size);
        // } else {
        //     transposition_end_index = std::min(transposition_end_index, number_of_nodes);
        // }
        // transposition_length = transposition_end_index - transposition_start_index;
        //
        // auto transposition_start_type = program->genotype_nodes[transposition_start_index]->node_type;
        //
        // auto start_index = -1;
        //
        // if (transposition_start_type == GEP_CONST || transposition_start_type == GEP_PARAM) {
        //     start_index = generator->generate() % (blueprint->head_size - 1) + 1;
        // } else {
        //     start_index = generator->generate() % blueprint->head_size;
        // }
        //
        // auto end_index = start_index + transposition_length;
        // end_index = std::min(end_index, blueprint->head_size - 1);
        // transposition_length = end_index - start_index;
        //
        // std::vector<GEPGenotypeNode*> new_nodes;
        // new_nodes.reserve(number_of_nodes);
        //
        // if (transposition_start_index < blueprint->head_size) {
        //
        //     if (transposition_start_index > start_index) {
        //         for (int i = 0; i < start_index; i++){
        //             new_nodes.push_back(program->genotype_nodes[i]);
        //         }
        //         for (int i = 0; i < transposition_length; i++) {
        //             new_nodes.push_back(program->genotype_nodes[transposition_start_index + i]);
        //         }
        //         for (int i = start_index; i < transposition_start_index; i++) {
        //             new_nodes.push_back(program->genotype_nodes[i]);
        //         }
        //         for (int i = transposition_end_index; i < blueprint->head_size; i++) {
        //             new_nodes.push_back(program->genotype_nodes[i]);
        //         }
        //     }
        //
        //     else {
        //         for (int i = 0; i < transposition_start_index; i++){
        //             new_nodes.push_back(program->genotype_nodes[i]);
        //         }
        //         for (int i = transposition_start_index; i < start_index; i++) {
        //             new_nodes.push_back(program->genotype_nodes[i + transposition_length]);
        //         }
        //         for (int i = 0; i < transposition_length; i++) {
        //             new_nodes.push_back(program->genotype_nodes[transposition_start_index + i]);
        //         }
        //         for (int i = end_index; i < blueprint->head_size; i++) {
        //             new_nodes.push_back(program->genotype_nodes[i]);
        //         }
        //     }
        //
        // }
        //
        // else {
        //     for (int i = 0; i < start_index; i++) {
        //         new_nodes.push_back(program->genotype_nodes[i]);
        //     }
        //     for (int i = 0; i < transposition_length; i++) {
        //         new_nodes.push_back(program->genotype_nodes[transposition_start_index + i]);
        //     }
        //     for (int i = end_index; i < blueprint->head_size; i++) {
        //         new_nodes.push_back(program->genotype_nodes[i - transposition_length]);
        //     }
        // }
        //
        // for (int i = blueprint->head_size; i < number_of_nodes; i++) {
        //     new_nodes.push_back(program->genotype_nodes[i]);
        // }
        //
        // program->genotype_nodes = new_nodes;


        auto transposition_start_index = generator->generate() % number_of_nodes;
        auto transposition_length = generator->generate() % transposition_max_length + 1;
        auto transposition_end_index = transposition_start_index + transposition_length;
        transposition_end_index = transposition_start_index < blueprint->head_size ?
            std::min(transposition_end_index, blueprint->head_size) :
            std::min(transposition_end_index, number_of_nodes);
        transposition_length = transposition_end_index - transposition_start_index;

        auto transposition_start_node_type = program->genotype_nodes[transposition_start_index]->node_type;

        auto start_index = transposition_start_node_type == GEP_CONST || transposition_start_node_type == GEP_PARAM ?
            generator->generate() % (blueprint->head_size - 1) + 1 :
            generator->generate() % blueprint->head_size;
        auto end_index = start_index + transposition_length;
        end_index = std::min(end_index, blueprint->head_size);

        transposition_length = end_index - start_index;
        transposition_end_index = transposition_start_index + transposition_length;

        std::vector<GEPGenotypeNode*> new_nodes;
        new_nodes.reserve(number_of_nodes);

        if (transposition_start_index < blueprint->head_size) {

            if (start_index < transposition_start_index) {

                for (int i = 0; i < start_index; i++) {
                    new_nodes.push_back(program->genotype_nodes[i]);
                }
                for (int i = 0; i < transposition_length; i++) {
                    new_nodes.push_back(program->genotype_nodes[transposition_start_index + i]);
                }
                for (int i = start_index; i < transposition_start_index; i++) {
                    new_nodes.push_back(program->genotype_nodes[i]);
                }
                for (int i = transposition_end_index; i < blueprint->head_size; i++) {
                    new_nodes.push_back(program->genotype_nodes[i]);
                }
            }

            else if (start_index > transposition_start_index) {

                for (int i = 0; i < transposition_start_index; i++) {
                    new_nodes.push_back(program->genotype_nodes[i]);
                }
                for (int i = transposition_end_index; i < end_index; i++) {
                    new_nodes.push_back(program->genotype_nodes[i]);
                }
                for (int i = 0; i < transposition_length; i++) {
                    new_nodes.push_back(program->genotype_nodes[transposition_start_index + i]);
                }
                for (int i = end_index; i < blueprint->head_size; i++) {
                    new_nodes.push_back(program->genotype_nodes[i]);
                }

            }

            else {
                for (int i = 0; i < blueprint->head_size; i++) {
                    new_nodes.push_back(program->genotype_nodes[i]);
                }
            }
        }

        else {
            for (int i = 0; i < start_index; i++) {
                new_nodes.push_back(program->genotype_nodes[i]);
            }
            for (int i = 0; i < transposition_length; i++) {
                new_nodes.push_back(program->genotype_nodes[transposition_start_index + i]->copy());
            }
            for (int i = end_index; i < blueprint->head_size; i++) {
                new_nodes.push_back(program->genotype_nodes[i - transposition_length]);
            }
            for (int i = blueprint->head_size - transposition_length; i < blueprint->head_size; i++) {
                delete program->genotype_nodes[i];
            }
        }

        for (int i = blueprint->head_size; i < number_of_nodes; i++) {
            new_nodes.push_back(program->genotype_nodes[i]);
        }

        program->genotype_nodes = new_nodes;
    }

    program->buildPhenotype();
}
