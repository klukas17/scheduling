//
// Created by mihael on 5/31/24.
//

#include "StructuredGrammaticalEvolutionSerializationOperator.h"

#include "SGEPhenotypeBuilder.h"
#include "SGEPhenotypeNodeConst.h"
#include "SGEPhenotypeNodeParam.h"
#include "StructuredGrammaticalEvolution.h"
#include "sstream"

StructuredGrammaticalEvolutionSerializationOperator::StructuredGrammaticalEvolutionSerializationOperator(StructuredGrammaticalEvolutionGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
}

StructuredGrammaticalEvolutionSerializationOperator::~StructuredGrammaticalEvolutionSerializationOperator() = default;

std::vector<std::string> StructuredGrammaticalEvolutionSerializationOperator::serialize(Genotype* genotype) {

    auto sge = dynamic_cast<StructuredGrammaticalEvolution*>(genotype);

    std::ostringstream oss;
    for (auto input : sge->getInputs()) {
        oss << input << " ";
    }
    std::vector<std::string> result = {oss.str()};

    auto constants = sge->getProgram()->collectAllConstants();
    oss.str("");
    oss << constants.size();
    result.push_back(oss.str());
    for (auto [key, value] : constants) {
        oss.str("");
        oss << key << " " << value;
        result.push_back(oss.str());
    }

    oss.str("");
    for (auto val : sge->getProgram()->symbol_values) {
        oss << val << " ";
    }
    result.push_back(oss.str());

    oss.str("");
    for (auto val : sge->getProgram()->terminal_values) {
        oss << val << " ";
    }
    result.push_back(oss.str());

    oss.str("");
    for (auto val : sge->getProgram()->nonterminal_values) {
        oss << val << " ";
    }
    result.push_back(oss.str());

    oss.str("");
    for (auto val : sge->getProgram()->param_values) {
        oss << val << " ";
    }
    result.push_back(oss.str());

    return result;
}

Genotype* StructuredGrammaticalEvolutionSerializationOperator::deserialize(std::vector<std::string> representation) {
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

    auto program_metadata = new SGEProgramMetadata(blueprint->max_depth, inputs);

    std::vector<int> symbol_values;
    std::vector<int> terminal_values;
    std::vector<int> nonterminal_values;
    std::vector<int> param_values;

    symbol_values.reserve(program_metadata->max_number_of_occurences[SGE_SYMBOL]);
    terminal_values.reserve(program_metadata->max_number_of_occurences[SGE_TERMINAL]);
    nonterminal_values.reserve(program_metadata->max_number_of_occurences[SGE_NONTERMINAL]);
    param_values.reserve(program_metadata->max_number_of_occurences[SGE_PARAM]);

    int n;

    iss.clear();
    iss.str(representation[index]);
    index++;
    while (iss >> n) {
        symbol_values.push_back(n);
    }

    iss.clear();
    iss.str(representation[index]);
    index++;
    while (iss >> n) {
        terminal_values.push_back(n);
    }

    iss.clear();
    iss.str(representation[index]);
    index++;
    while (iss >> n) {
        nonterminal_values.push_back(n);
    }

    iss.clear();
    iss.str(representation[index]);
    index++;
    while (iss >> n) {
        param_values.push_back(n);
    }

    auto program = new SGEProgram(
        program_metadata,
        symbol_values,
        terminal_values,
        nonterminal_values,
        param_values
    );
    auto sge = new StructuredGrammaticalEvolution(program);
    sge->setInputs(inputs);
    SGEPhenotypeBuilder::buildPhenotype(sge, blueprint, constant_map);
    return sge;
}

std::vector<std::string> StructuredGrammaticalEvolutionSerializationOperator::serializePhenotype(Genotype* genotype) {
    auto sge = dynamic_cast<StructuredGrammaticalEvolution*>(genotype);
    return serializePhenotypeNode(sge->getProgram()->phenotype_root_node, 0);
}

std::vector<std::string> StructuredGrammaticalEvolutionSerializationOperator::serializePhenotypeNode(SGEPhenotypeNode* node, int depth) {
    std::ostringstream oss;

    for (int i = 0; i < depth; i++) {
        oss << " ";
    }

    std::vector<std::string> children_node_lines;

    switch(node->node_type) {

    case SGE_SYMBOL:
        {
            oss << "SYMBOL";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case SGE_TERMINAL:
        {
            oss << "TERMINAL";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case SGE_NONTERMINAL:
        {
            oss << "NONTERMINAL";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case SGE_CONST:
        {
            oss << "CONST";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case SGE_PARAM:
        {
            oss << "PARAM";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case SGE_UNARY_MINUS:
        {
            oss << "UNARY_MINUS";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case SGE_PLUS:
        {
            oss << "PLUS";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case SGE_MINUS:
        {
            oss << "MINUS";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case SGE_TIMES:
        {
            oss << "TIMES";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case SGE_DIVIDE:
        {
            oss << "DIVIDE";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case SGE_SQUARE:
        {
            oss << "SQUARE";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case SGE_ROOT:
        {
            oss << "ROOT";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case SGE_BRANCH:
        {
            oss << "BRANCH";
            for (auto child : node->children) {
                for (const auto& line : serializePhenotypeNode(child, depth + 1)) {
                    children_node_lines.push_back(line);
                }
            }
            break;
        }

    case SGE_LEAF_CONST:
        {
            oss << "LEAF_CONST " << dynamic_cast<SGEPhenotypeNodeConst*>(node)->constant;
            break;
        }

    case SGE_LEAF_PARAM:
        {
            oss << "LEAF_PARAM " << dynamic_cast<SGEPhenotypeNodeParam*>(node)->param;
            break;
        }

    }

    std::vector<std::string> result = {oss.str()};
    for (const auto& line : children_node_lines) {
        result.push_back(line);
    }

    return result;
}
