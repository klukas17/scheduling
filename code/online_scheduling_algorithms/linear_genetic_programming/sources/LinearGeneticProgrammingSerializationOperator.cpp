//
// Created by mihael on 5/27/24.
//

#include "LinearGeneticProgrammingSerializationOperator.h"

#include "LinearGeneticProgramming.h"
#include "sstream"

LinearGeneticProgrammingSerializationOperator::LinearGeneticProgrammingSerializationOperator(LinearGeneticProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
}

LinearGeneticProgrammingSerializationOperator::~LinearGeneticProgrammingSerializationOperator() = default;

std::vector<std::string> LinearGeneticProgrammingSerializationOperator::serialize(Genotype* genotype) {
    auto lgp = dynamic_cast<LinearGeneticProgramming*>(genotype);

    std::ostringstream oss;
    for (auto input : lgp->getInputs()) {
        oss << input << " ";
    }
    std::vector<std::string> result = {oss.str()};

    auto constants = lgp->getProgram()->load_constant_map;
    oss.str("");
    oss << constants.size();
    result.push_back(oss.str());
    for (auto [key, value] : constants) {
        oss.str("");
        oss << key << " " << value;
        result.push_back(oss.str());
    }

    auto params = lgp->getProgram()->load_param_map;
    oss.str("");
    oss << params.size();
    result.push_back(oss.str());
    for (auto [key, value] : params) {
        oss.str("");
        oss << key << " " << value;
        result.push_back(oss.str());
    }

    for (auto instruction : lgp->getProgram()->instructions) {
        oss.str("");
        oss << instruction->instruction_id << " " << instruction->instruction_type << " " << instruction->first_register_id << " " << instruction->second_register_id << " " << instruction->third_register_id;
        result.push_back(oss.str());
    }

    return result;
}

Genotype* LinearGeneticProgrammingSerializationOperator::deserialize(std::vector<std::string> representation) {
    std::istringstream iss(representation[0]);
    std::vector<std::string> inputs;
    std::string input;
    while (iss >> input) {
        inputs.push_back(input);
    }

    int constants_number = std::stoi(representation[1]);
    std::map<int, double> load_constant_map;
    int index = 2;
    for (int i = 0; i < constants_number; i++) {
        int instruction_index;
        double constant;
        std::istringstream iss(representation[index]);
        iss >> instruction_index;
        iss >> constant;
        load_constant_map[instruction_index] = constant;
        index++;
    }

    int params_number = std::stoi(representation[index]);
    std::map<int, std::string> load_param_map;
    index++;
    for (int i = 0; i < params_number; i++) {
        int instruction_index;
        std::string param;
        std::istringstream iss(representation[index]);
        iss >> instruction_index;
        iss >> param;
        load_param_map[instruction_index] = param;
        index++;
    }

    std::vector<LGPInstruction*> instructions;

    for (int i = 0; i < blueprint->number_of_instructions; i++) {
        std::istringstream iss(representation[index]);
        int instruction_id, instruction_type, first_register_index, second_register_index, third_register_index;
        iss >> instruction_id >> instruction_type >> first_register_index >> second_register_index >> third_register_index;
        instructions.push_back(new LGPInstruction(
            static_cast<LGPInstructionType>(instruction_type),
            first_register_index,
            second_register_index,
            third_register_index,
            instruction_id
        ));
        index++;
    }

    auto lgp = new LinearGeneticProgramming(
        new LGPProgram(
            instructions,
            load_constant_map,
            load_param_map
        ),
        blueprint->register_initialization_strategy,
        blueprint->number_of_registers
    );
    lgp->setInputs(inputs);

    return lgp;
}
