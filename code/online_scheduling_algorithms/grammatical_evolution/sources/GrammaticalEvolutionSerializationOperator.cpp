//
// Created by mihael on 5/30/24.
//

#include "GrammaticalEvolutionSerializationOperator.h"

#include "GEPhenotypeBuilder.h"
#include "GEPhenotypeNodeConst.h"
#include "GEPhenotypeNodeParam.h"
#include "sstream"
#include "GrammaticalEvolution.h"

GrammaticalEvolutionSerializationOperator::GrammaticalEvolutionSerializationOperator(GrammaticalEvolutionGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
}

std::vector<std::string> GrammaticalEvolutionSerializationOperator::serialize(Genotype* genotype) {

    auto ge = dynamic_cast<GrammaticalEvolution*>(genotype);

    std::ostringstream oss;
    for (auto input : ge->getInputs()) {
        oss << input << " ";
    }
    std::vector<std::string> result = {oss.str()};

    auto constants = ge->getProgram()->collectAllConstants();
    oss.str("");
    oss << constants.size();
    result.push_back(oss.str());
    for (auto [key, value] : constants) {
        oss.str("");
        oss << key << " " << value;
        result.push_back(oss.str());
    }

    for (auto node : ge->getProgram()->genotype_nodes) {
        oss.str("");
        oss << node->node_id << " " << node->codon_value;
        result.push_back(oss.str());
    }

    return result;
}

Genotype* GrammaticalEvolutionSerializationOperator::deserialize(std::vector<std::string> representation) {
    std::istringstream iss(representation[0]);
    std::vector<std::string> inputs;
    std::string input;
    while (iss >> input) {
        inputs.push_back(input);
    }

    int constants_number = std::stoi(representation[1]);
    std::map<int, double> constant_map;
    int index = 2;
    for (int i = 0; i < constants_number; i++) {
        int instruction_index;
        double constant;
        std::istringstream iss(representation[index]);
        iss >> instruction_index;
        iss >> constant;
        constant_map[instruction_index] = constant;
        index++;
    }

    std::vector<GEGenotypeNode*> nodes;

    for (int i = 0; i < blueprint->codons; i++) {
        std::istringstream iss(representation[index]);
        int node_id, codon_value;
        iss >> node_id >> codon_value;
        nodes.push_back(new GEGenotypeNode(
            node_id,
            codon_value
        ));
        index++;
    }


    auto ge = new GrammaticalEvolution(new GEProgram(nodes));
    ge->setInputs(inputs);
    GEPhenotypeBuilder::buildPhenotype(ge, blueprint, constant_map);

    return ge;
}

std::vector<std::string> GrammaticalEvolutionSerializationOperator::serializePhenotype(Genotype* genotype) {
    auto ge = dynamic_cast<GrammaticalEvolution*>(genotype);
    return serializePhenotypeNode(ge->getProgram()->phenotype_root_node, 0);
}

std::vector<std::string> GrammaticalEvolutionSerializationOperator::serializePhenotypeNode(GEPhenotypeNode* node, int depth) {

    std::ostringstream oss;

    for (int i = 0; i < depth; i++) {
        oss << " ";
    }

    std::vector<std::string> children_node_lines;

    switch(node->node_type) {

    case GE_SYMBOL:
        {
            oss << "SYMBOL";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GE_TERMINAL:
        {
            oss << "TERMINAL";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GE_NONTERMINAL:
        {
            oss << "NONTERMINAL";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GE_CONST:
        {
            oss << "CONST";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GE_PARAM:
        {
            oss << "PARAM";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GE_UNARY_MINUS:
        {
            oss << "UNARY_MINUS";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GE_PLUS:
        {
            oss << "PLUS";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GE_MINUS:
        {
            oss << "MINUS";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GE_TIMES:
        {
            oss << "TIMES";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GE_DIVIDE:
        {
            oss << "DIVIDE";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GE_SQUARE:
        {
            oss << "SQUARE";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GE_ROOT:
        {
            oss << "ROOT";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GE_BRANCH:
        {
            oss << "BRANCH";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GE_LEAF_CONST:
        {
            oss << "LEAF_CONST " << dynamic_cast<GEPhenotypeNodeConst*>(node)->constant;
            break;
        }

    case GE_LEAF_PARAM:
        {
            oss << "LEAF_PARAM " << dynamic_cast<GEPhenotypeNodeParam*>(node)->param;
            break;
        }

    }

    std::vector<std::string> result = {oss.str()};
    for (const auto& line : children_node_lines) {
        result.push_back(line);
    }

    return result;
}
