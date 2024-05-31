//
// Created by mihael on 5/31/24.
//

#include "GEPhenotypeBuilder.h"

#include "GEPhenotypeNodeConst.h"
#include "GEPhenotypeNodeParam.h"

void GEPhenotypeBuilder::buildPhenotype(
    GrammaticalEvolution* ge,
    GrammaticalEvolutionGenotypeBlueprint* blueprint,
    const std::map<int, double>& prepopulated_constants_map
) {
    int codon_index = 0;
    int number_of_wrappings = 0;
    int node_id = 0;
    bool mapping_failed = false;

    if (ge->getProgram()->phenotype_root_node != nullptr) {
        delete ge->getProgram()->phenotype_root_node;
        ge->getProgram()->phenotype_root_node = nullptr;
    }

    auto phenotype_root_node = new GEPhenotypeNode(0, GE_SYMBOL);
    node_id++;

    buildPhenotypeNode(
        phenotype_root_node,
        ge,
        blueprint,
        prepopulated_constants_map,
        codon_index,
        number_of_wrappings,
        node_id,
        mapping_failed
    );

    if (mapping_failed) {
        delete phenotype_root_node;
        ge->getProgram()->phenotype_root_node = nullptr;
    } else {
        ge->getProgram()->phenotype_root_node = phenotype_root_node;
    }
}

void GEPhenotypeBuilder::buildPhenotypeNode(
    GEPhenotypeNode* node,
    GrammaticalEvolution* ge,
    GrammaticalEvolutionGenotypeBlueprint* blueprint,
    const std::map<int, double>& prepopulated_constants_map,
    int& codon_index,
    int& number_of_wrappings,
    int& node_id,
    bool& mapping_failed
) {

    if (number_of_wrappings == blueprint->max_number_of_wrapping + 1) {
        mapping_failed = true;
        return;
    }

    switch(node->node_type) {

    case GE_SYMBOL:
    case GE_TERMINAL:
    case GE_NONTERMINAL:
        {
            auto productions = blueprint->grammar->productions[node->node_type];
            auto child_node_type = productions[ge->getProgram()->genotype_nodes[codon_index]->codon_value % productions.size()];
            codon_index++;
            if (codon_index == blueprint->codons) {
                codon_index = 0;
                number_of_wrappings++;
            }
            auto child_node = new GEPhenotypeNode(node_id, child_node_type);
            node_id++;
            node->children.push_back(child_node);
            buildPhenotypeNode(
                child_node,
                ge,
                blueprint,
                prepopulated_constants_map,
                codon_index,
                number_of_wrappings,
                node_id,
                mapping_failed
            );
            break;
        }

    case GE_UNARY_MINUS:
    case GE_SQUARE:
    case GE_ROOT:
        {
            auto child_node = new GEPhenotypeNode(node_id, GE_SYMBOL);
            node_id++;
            node->children.push_back(child_node);
            buildPhenotypeNode(
                child_node,
                ge,
                blueprint,
                prepopulated_constants_map,
                codon_index,
                number_of_wrappings,
                node_id,
                mapping_failed
            );
            break;
        }

    case GE_PLUS:
    case GE_MINUS:
    case GE_TIMES:
    case GE_DIVIDE:
        {
            for (int i = 0; i < 2; i++) {
                auto child_node = new GEPhenotypeNode(node_id, GE_SYMBOL);
                node_id++;
                node->children.push_back(child_node);
                buildPhenotypeNode(
                    child_node,
                    ge,
                    blueprint,
                    prepopulated_constants_map,
                    codon_index,
                    number_of_wrappings,
                    node_id,
                    mapping_failed
                );
                if (mapping_failed) {
                    return;
                }
            }
            break;
        }

    case GE_BRANCH:
        {
            for (int i = 0; i < 3; i++) {
                auto child_node = new GEPhenotypeNode(node_id, GE_SYMBOL);
                node_id++;
                node->children.push_back(child_node);
                buildPhenotypeNode(
                    child_node,
                    ge,
                    blueprint,
                    prepopulated_constants_map,
                    codon_index,
                    number_of_wrappings,
                    node_id,
                    mapping_failed
                );
                if (mapping_failed) {
                    return;
                }
            }
            break;
        }

    case GE_CONST:
        {
            auto child_node = new GEPhenotypeNodeConst(
                node_id,
                GE_LEAF_CONST,
                prepopulated_constants_map.contains(node_id) ? prepopulated_constants_map.at(node_id) : blueprint->generateConstant()
            );
            node_id++;
            node->children.push_back(child_node);
            break;
        }

    case GE_PARAM:
        {
            auto inputs = ge->getInputs();
            auto param = inputs[ge->getProgram()->genotype_nodes[codon_index]->codon_value % inputs.size()];
            codon_index++;
            if (codon_index == blueprint->codons) {
                codon_index = 0;
                number_of_wrappings++;
            }
            auto child_node = new GEPhenotypeNodeParam(node_id, GE_LEAF_PARAM, param);
            node_id++;
            node->children.push_back(child_node);
            break;
        }

    case GE_LEAF_CONST:
    case GE_LEAF_PARAM:
        {
            break;
        }
    }
}


