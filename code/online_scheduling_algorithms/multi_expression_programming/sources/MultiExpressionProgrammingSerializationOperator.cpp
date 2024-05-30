//
// Created by mihael on 5/30/24.
//

#include "MultiExpressionProgrammingSerializationOperator.h"
#include "sstream"
#include "MultiExpressionProgramming.h"

MultiExpressionProgrammingSerializationOperator::MultiExpressionProgrammingSerializationOperator(MultiExpressionProgrammingGenotypeBlueprint* blueprint) {
    this->blueprint = blueprint;
}

std::vector<std::string> MultiExpressionProgrammingSerializationOperator::serialize(Genotype* genotype) {
    auto mep = dynamic_cast<MultiExpressionProgramming*>(genotype);

    std::ostringstream oss;
    for (auto input : mep->getInputs()) {
        oss << input << " ";
    }
    std::vector<std::string> result = {oss.str()};

    auto constants = mep->getProgram()->constant_map;
    oss.str("");
    oss << constants.size();
    result.push_back(oss.str());
    for (auto [key, value] : constants) {
        oss.str("");
        oss << key << " " << value;
        result.push_back(oss.str());
    }

    auto params = mep->getProgram()->param_map;
    oss.str("");
    oss << params.size();
    result.push_back(oss.str());
    for (auto [key, value] : params) {
        oss.str("");
        oss << key << " " << value;
        result.push_back(oss.str());
    }

    for (auto instruction : mep->getProgram()->instructions) {
        oss.str("");
        oss << instruction->instruction_id << " " << instruction->instruction_type << " " << instruction->first_param << " " << instruction->second_param << " " << instruction->third_param;
        result.push_back(oss.str());
    }

    return result;
}

Genotype* MultiExpressionProgrammingSerializationOperator::deserialize(std::vector<std::string> representation) {
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

    std::vector<MEPInstruction*> instructions;

    for (int i = 0; i < blueprint->number_of_instructions; i++) {
        std::istringstream iss(representation[index]);
        int instruction_id, instruction_type, first_param, second_param, third_param;
        iss >> instruction_id >> instruction_type >> first_param >> second_param >> third_param;
        instructions.push_back(new MEPInstruction(
            instruction_id,
            static_cast<MEPInstructionType>(instruction_type),
            first_param,
            second_param,
            third_param
        ));
        index++;
    }

    auto mep = new MultiExpressionProgramming(
        new MEPProgram(
            instructions,
            constant_map,
            param_map
        )
    );
    mep->setInputs(inputs);

    return mep;
}

