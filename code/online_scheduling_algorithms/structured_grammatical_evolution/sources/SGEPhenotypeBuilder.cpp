//
// Created by mihael on 5/31/24.
//

#include "SGEPhenotypeBuilder.h"

#include "SGEPhenotypeNodeConst.h"
#include "SGEPhenotypeNodeParam.h"

void SGEPhenotypeBuilder::buildPhenotype(
    StructuredGrammaticalEvolution* sge,
    StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint,
    const std::map<int, double>& prepopulated_constants_map
) {
    int codon_index = 0;
    int node_id = 0;
    int symbol_values_index = 0;
    int terminal_values_index = 0;
    int nonterminal_values_index = 0;
    int param_values_index = 0;

    if (sge->getProgram()->phenotype_root_node != nullptr) {
        delete sge->getProgram()->phenotype_root_node;
        sge->getProgram()->phenotype_root_node = nullptr;
    }

    auto phenotype_root_node = new SGEPhenotypeNode(0, 0, SGE_SYMBOL);
    node_id++;

    sge->getProgram()->phenotype_root_node = phenotype_root_node;

    buildPhenotypeNode(
        phenotype_root_node,
        sge,
        blueprint,
        prepopulated_constants_map,
        codon_index,
        node_id,
        symbol_values_index,
        terminal_values_index,
        nonterminal_values_index,
        param_values_index
    );
}

void SGEPhenotypeBuilder::buildPhenotypeNode(
    SGEPhenotypeNode* node,
    StructuredGrammaticalEvolution* sge,
    StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint,
    const std::map<int, double>& prepopulated_constants_map,
    int& codon_index,
    int& node_id,
    int& symbol_values_index,
    int& terminal_values_index,
    int& nonterminal_values_index,
    int& param_values_index
) {

    switch(node->node_type)
    {

    case SGE_SYMBOL:
        {
            SGENodeType child_node_type;
            if (node->depth >= blueprint->max_depth) {
                child_node_type = SGE_TERMINAL;
            } else {
                child_node_type = blueprint->grammar->productions[node->node_type][sge->getProgram()->symbol_values[symbol_values_index]];
                symbol_values_index++;
            }
            auto child_node = new SGEPhenotypeNode(
                node_id,
                child_node_type == SGE_NONTERMINAL ? node->depth + 1 : node->depth,
                child_node_type
            );
            node_id++;
            node->children.push_back(child_node);
            buildPhenotypeNode(
                child_node,
                sge,
                blueprint,
                prepopulated_constants_map,
                codon_index,
                node_id,
                symbol_values_index,
                terminal_values_index,
                nonterminal_values_index,
                param_values_index
            );
            break;
        }

    case SGE_TERMINAL:{
            auto child_node_type = blueprint->grammar->productions[node->node_type][sge->getProgram()->terminal_values[terminal_values_index]];
            terminal_values_index++;
            auto child_node = new SGEPhenotypeNode(
                node_id,
                node->depth,
                child_node_type
            );
            node_id++;
            node->children.push_back(child_node);
            buildPhenotypeNode(
                child_node,
                sge,
                blueprint,
                prepopulated_constants_map,
                codon_index,
                node_id,
                symbol_values_index,
                terminal_values_index,
                nonterminal_values_index,
                param_values_index
            );
            break;
    }

    case SGE_NONTERMINAL:
        {
            auto child_node_type = blueprint->grammar->productions[node->node_type][sge->getProgram()->nonterminal_values[nonterminal_values_index]];
            nonterminal_values_index++;
            auto child_node = new SGEPhenotypeNode(
                node_id,
                node->depth,
                child_node_type
            );
            node_id++;
            node->children.push_back(child_node);
            buildPhenotypeNode(
                child_node,
                sge,
                blueprint,
                prepopulated_constants_map,
                codon_index,
                node_id,
                symbol_values_index,
                terminal_values_index,
                nonterminal_values_index,
                param_values_index
            );
            break;
        }

    case SGE_UNARY_MINUS:
    case SGE_SQUARE:
    case SGE_ROOT:
        {
            auto child_node = new SGEPhenotypeNode(
                node_id,
                node->depth,
                SGE_SYMBOL
            );
            node_id++;
            node->children.push_back(child_node);
            buildPhenotypeNode(
                child_node,
                sge,
                blueprint,
                prepopulated_constants_map,
                codon_index,
                node_id,
                symbol_values_index,
                terminal_values_index,
                nonterminal_values_index,
                param_values_index
            );
            break;
        }

    case SGE_PLUS:
    case SGE_MINUS:
    case SGE_TIMES:
    case SGE_DIVIDE:
        {
            for (int i = 0; i < 2; i++) {
                auto child_node = new SGEPhenotypeNode(
                    node_id,
                    node->depth,
                    SGE_SYMBOL
                );
                node_id++;
                node->children.push_back(child_node);
                buildPhenotypeNode(
                    child_node,
                    sge,
                    blueprint,
                    prepopulated_constants_map,
                    codon_index,
                    node_id,
                    symbol_values_index,
                    terminal_values_index,
                    nonterminal_values_index,
                    param_values_index
                );
            }
            break;
        }

    case SGE_BRANCH:
        {
            for (int i = 0; i < 3; i++) {
                auto child_node = new SGEPhenotypeNode(
                    node_id,
                    node->depth,
                    SGE_SYMBOL
                );
                node_id++;
                node->children.push_back(child_node);
                buildPhenotypeNode(
                    child_node,
                    sge,
                    blueprint,
                    prepopulated_constants_map,
                    codon_index,
                    node_id,
                    symbol_values_index,
                    terminal_values_index,
                    nonterminal_values_index,
                    param_values_index
                );
            }
            break;
        }

    case SGE_CONST:
        {
            auto child_node = new SGEPhenotypeNodeConst(
                node_id,
                node->depth,
                SGE_LEAF_CONST,
                prepopulated_constants_map.contains(node_id) ? prepopulated_constants_map.at(node_id) : blueprint->generateConstant()
            );
            node_id++;
            node->children.push_back(child_node);
            break;
        }

    case SGE_PARAM:
        {
            auto inputs = sge->getInputs();
            auto param_index = sge->getProgram()->param_values[param_values_index];
            param_values_index++;
            auto param = inputs[param_index];
            auto child_node = new SGEPhenotypeNodeParam(
                node_id,
                node->depth,
                SGE_LEAF_PARAM,
                param
            );
            node_id++;
            node->children.push_back(child_node);
            break;
        }

    case SGE_LEAF_CONST:
    case SGE_LEAF_PARAM:
        {
            break;
        }

    }
}
