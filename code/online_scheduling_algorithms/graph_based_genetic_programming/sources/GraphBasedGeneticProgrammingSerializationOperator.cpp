//
// Created by mihael on 6/1/24.
//

#include "GraphBasedGeneticProgrammingSerializationOperator.h"

#include <ranges>

#include "GraphBasedGeneticProgramming.h"
#include "sstream"

GraphBasedGeneticProgrammingSerializationOperator::GraphBasedGeneticProgrammingSerializationOperator(GraphBasedGeneticProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
}

GraphBasedGeneticProgrammingSerializationOperator::~GraphBasedGeneticProgrammingSerializationOperator() = default;

std::vector<std::string> GraphBasedGeneticProgrammingSerializationOperator::serialize(Genotype* genotype) {
    auto gbgp = dynamic_cast<GraphBasedGeneticProgramming*>(genotype);
    auto program = gbgp->getProgram();

    std::ostringstream oss;
    for (auto input : gbgp->getInputs()) {
        oss << input << " ";
    }
    std::vector<std::string> result = {oss.str()};

    oss.str("");
    oss << program->output_node_id;
    result.push_back(oss.str());

    auto constants = program->constant_map;
    oss.str("");
    oss << constants.size();
    result.push_back(oss.str());
    for (auto [key, value] : constants) {
        oss.str("");
        oss << key << " " << value;
        result.push_back(oss.str());
    }

    oss.str("");
    for (auto val : program->free_node_ids) {
        oss << val << " ";
    }
    result.push_back(oss.str());

    oss.str("");
    oss << program->nodes.size();
    result.push_back(oss.str());

    for (auto node : program->nodes | std::ranges::views::values) {
        oss.str("");
        oss << node->node_id << " " << node->node_type << " " << node->first_predecessor_index << " " << node->second_predecessor_index << " " << node->third_predecessor_index;
        result.push_back(oss.str());
    }

    return result;
}

Genotype* GraphBasedGeneticProgrammingSerializationOperator::deserialize(std::vector<std::string> representation) {
    std::istringstream iss(representation[0]);
    std::vector<std::string> inputs;
    std::string input;
    while (iss >> input) {
        inputs.push_back(input);
    }

    int output_index = std::stoi(representation[1]);

    int constants_number = std::stoi(representation[2]);
    std::map<int, double> constants_map;
    int index = 3;
    for (int i = 0; i < constants_number; i++) {
        long cell_index;
        double constant;
        std::istringstream iss(representation[index]);
        iss >> cell_index;
        iss >> constant;
        constants_map[cell_index] = constant;
        index++;
    }

    std::set<int> free_node_ids;
    int i;

    iss.clear();
    iss.str(representation[index]);
    index++;
    while (iss >> i) {
        free_node_ids.insert(i);
    }

    std::map<int, GBGPNode*> nodes;
    std::map<int, std::set<int>> from_nodes;
    std::map<int, std::set<int>> to_nodes;

    int nodes_number = std::stoi(representation[index]);
    index++;

    for (int i = 0; i < nodes_number; i++) {
        std::istringstream iss(representation[index]);
        int node_id, node_type, first_predecessor_index, second_predecessor_index, third_predecessor_index;
        iss >> node_id >> node_type >> first_predecessor_index >> second_predecessor_index >> third_predecessor_index;

        from_nodes[node_id].insert(first_predecessor_index);
        from_nodes[node_id].insert(second_predecessor_index);
        from_nodes[node_id].insert(third_predecessor_index);

        to_nodes[first_predecessor_index].insert(node_id);
        to_nodes[second_predecessor_index].insert(node_id);
        to_nodes[third_predecessor_index].insert(node_id);

        nodes[node_id] = new GBGPNode(
            node_id,
            static_cast<GBGPNodeType>(node_type),
            first_predecessor_index,
            second_predecessor_index,
            third_predecessor_index
        );

        index++;
    }

    auto program = new GBGPProgram(
        nodes,
        constants_map,
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
