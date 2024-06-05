//
// Created by mihael on 5/29/24.
//

#include "GeneExpressionProgrammingSerializationOperator.h"

#include "GeneExpressionProgramming.h"
#include "sstream"

GeneExpressionProgrammingSerializationOperator::GeneExpressionProgrammingSerializationOperator(GeneExpressionProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
}

GeneExpressionProgrammingSerializationOperator::~GeneExpressionProgrammingSerializationOperator() = default;

std::vector<std::string> GeneExpressionProgrammingSerializationOperator::serialize(Genotype* genotype) {
    auto gep = dynamic_cast<GeneExpressionProgramming*>(genotype);

    std::ostringstream oss;
    for (auto input : gep->getInputs()) {
        oss << input << " ";
    }
    std::vector<std::string> result = {oss.str()};

    auto constants = gep->getProgram()->constant_map;
    oss.str("");
    oss << constants.size();
    result.push_back(oss.str());
    for (auto [key, value] : constants) {
        oss.str("");
        oss << key << " " << value;
        result.push_back(oss.str());
    }

    auto params = gep->getProgram()->param_map;
    oss.str("");
    oss << params.size();
    result.push_back(oss.str());
    for (const auto& [key, value] : params) {
        oss.str("");
        oss << key << " " << value;
        result.push_back(oss.str());
    }

    for (auto node : gep->getProgram()->genotype_nodes) {
        oss.str("");
        oss << node->node_id << " " << node->node_type;
        result.push_back(oss.str());
    }

    return result;
}

Genotype* GeneExpressionProgrammingSerializationOperator::deserialize(std::vector<std::string> representation) {

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

    int params_number = std::stoi(representation[index]);
    std::map<int, std::string> param_map;
    index++;
    for (int i = 0; i < params_number; i++) {
        int instruction_index;
        std::string param;
        std::istringstream iss(representation[index]);
        iss >> instruction_index;
        iss >> param;
        param_map[instruction_index] = param;
        index++;
    }

    std::vector<GEPGenotypeNode*> nodes;

    for (int i = 0; i < blueprint->head_size + blueprint->tail_size; i++) {
        std::istringstream iss(representation[index]);
        int node_id, node_type;
        iss >> node_id >> node_type;
        nodes.push_back(new GEPGenotypeNode(
            node_id,
            static_cast<GEPNodeType>(node_type)
        ));
        index++;
    }

    auto gep = new GeneExpressionProgramming(
        new GEPProgram(
            nodes,
            constant_map,
            param_map
        )
    );
    gep->setInputs(inputs);

    return gep;
}

std::vector<std::string> GeneExpressionProgrammingSerializationOperator::serializePhenotype(Genotype* genotype) {
    auto gep = dynamic_cast<GeneExpressionProgramming*>(genotype);
    return serializePhenotypeNode(gep->getProgram()->phenotype_root_node, gep->getProgram(), 0);
}

std::vector<std::string> GeneExpressionProgrammingSerializationOperator::serializePhenotypeNode(GEPPhenotypeNode* node, GEPProgram* program, int depth) {

    std::ostringstream oss;

    for (int i = 0; i < depth; i++) {
        oss << " ";
    }

    std::vector<std::string> children_node_lines;

    switch (node->node_type) {

    case GEP_CONST:
        {
            oss << "CONST " << program->constant_map[node->node_id];
            break;
        }

    case GEP_PARAM:
        {
            oss << "PARAM " << program->param_map[node->node_id];
            break;
        }

    case GEP_UNARY_MINUS:
        {
            oss << "UNARY_MINUS";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, program, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GEP_PLUS:
        {
            oss << "PLUS";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, program, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GEP_MINUS:
        {
            oss << "MINUS";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, program, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GEP_TIMES:
        {
            oss << "TIMES";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, program, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GEP_DIVIDE:
        {
            oss << "DIVIDE";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, program, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GEP_SQUARE:
        {
            oss << "SQUARE";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, program, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GEP_ROOT:
        {
            oss << "ROOT";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, program, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case GEP_BRANCH:
        {
            oss << "BRANCH";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, program, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    }

    std::vector<std::string> result = {oss.str()};
    for (const auto& line : children_node_lines) {
        result.push_back(line);
    }

    return result;
}
