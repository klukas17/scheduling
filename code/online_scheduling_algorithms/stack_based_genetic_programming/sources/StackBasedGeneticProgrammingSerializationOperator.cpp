//
// Created by mihael on 5/29/24.
//

#include "StackBasedGeneticProgrammingSerializationOperator.h"
#include "sstream"
#include "StackBasedGeneticProgramming.h"

StackBasedGeneticProgrammingSerializationOperator::StackBasedGeneticProgrammingSerializationOperator(StackBasedGeneticProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
}

std::vector<std::string> StackBasedGeneticProgrammingSerializationOperator::serialize(Genotype* genotype) {
    auto sbgp = dynamic_cast<StackBasedGeneticProgramming*>(genotype);

    std::ostringstream oss;
    for (auto input : sbgp->getInputs()) {
        oss << input << " ";
    }
    std::vector<std::string> result = {oss.str()};

    auto constants = sbgp->getProgram()->push_constant_map;
    oss.str("");
    oss << constants.size();
    result.push_back(oss.str());
    for (auto [key, value] : constants) {
        oss.str("");
        oss << key << " " << value;
        result.push_back(oss.str());
    }

    auto params = sbgp->getProgram()->push_param_map;
    oss.str("");
    oss << params.size();
    result.push_back(oss.str());
    for (auto [key, value] : params) {
        oss.str("");
        oss << key << " " << value;
        result.push_back(oss.str());
    }

    for (auto instruction : sbgp->getProgram()->instructions) {
        oss.str("");
        oss << instruction->instruction_id << " " << instruction->instruction_type;
        result.push_back(oss.str());
    }

    return result;
}

Genotype* StackBasedGeneticProgrammingSerializationOperator::deserialize(std::vector<std::string> representation) {
    std::istringstream iss(representation[0]);
    std::vector<std::string> inputs;
    std::string input;
    while (iss >> input) {
        inputs.push_back(input);
    }

    int constants_number = std::stoi(representation[1]);
    std::map<int, double> push_constant_map;
    int index = 2;
    for (int i = 0; i < constants_number; i++) {
        int instruction_index;
        double constant;
        std::istringstream iss(representation[index]);
        iss >> instruction_index;
        iss >> constant;
        push_constant_map[instruction_index] = constant;
        index++;
    }

    int params_number = std::stoi(representation[index]);
    std::map<int, std::string> push_param_map;
    index++;
    for (int i = 0; i < params_number; i++) {
        int instruction_index;
        std::string param;
        std::istringstream iss(representation[index]);
        iss >> instruction_index;
        iss >> param;
        push_param_map[instruction_index] = param;
        index++;
    }

    std::vector<SBGPInstruction*> instructions;

    for (int i = 0; i < blueprint->number_of_instructions; i++) {
        std::istringstream iss(representation[index]);
        int instruction_id, instruction_type;
        iss >> instruction_id >> instruction_type;
        instructions.push_back(new SBGPInstruction(
            static_cast<SBGPInstructionType>(instruction_type),
            instruction_id
        ));
        index++;
    }

    auto sbgp = new StackBasedGeneticProgramming(
        new SBGPProgram(
            instructions,
            push_constant_map,
            push_param_map
        )
    );
    sbgp->setInputs(inputs);

    return sbgp;
}
