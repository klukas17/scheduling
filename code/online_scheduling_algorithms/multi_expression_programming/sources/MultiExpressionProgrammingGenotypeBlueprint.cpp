//
// Created by mihael on 5/30/24.
//

#include "MultiExpressionProgrammingGenotypeBlueprint.h"

#include <climits>

#include "UniformIntDistributionGenerator.h"
#include "UniformRealDistributionGenerator.h"

MultiExpressionProgrammingGenotypeBlueprint::MultiExpressionProgrammingGenotypeBlueprint(int number_of_instructions, double constant_min, double constant_max) {
    this->number_of_instructions = number_of_instructions;
    this->constant_generator = new UniformRealDistributionGenerator(constant_min, constant_max);
    this->instruction_type_generator = new UniformRealDistributionGenerator(0, 1);
    this->generator = new UniformIntDistributionGenerator(0, INT_MAX);

    this->nullary_functions = {
        MEP_CONSTANT,
        MEP_PARAM
    };
    nullary_functions_probabilites.reserve(nullary_functions.size());
    auto segment = 1.0 / nullary_functions.size();
    for (int i = 0; i < nullary_functions.size() - 1; i++) {
        nullary_functions_probabilites.push_back(segment * (i + 1));
    }
    nullary_functions_probabilites.push_back(1);

    this->unary_functions = {
        MEP_CONSTANT,
        MEP_PARAM,
        MEP_UNARY_MINUS,
        MEP_SQUARE,
        MEP_ROOT
    };
    unary_functions_probabilites.reserve(unary_functions.size());
    segment = 1.0 / unary_functions.size();
    for (int i = 0; i < unary_functions.size() - 1; i++) {
        unary_functions_probabilites.push_back(segment * (i + 1));
    }
    unary_functions_probabilites.push_back(1);

    this->binary_functions = {
        MEP_CONSTANT,
        MEP_PARAM,
        MEP_UNARY_MINUS,
        MEP_SQUARE,
        MEP_ROOT,
        MEP_PLUS,
        MEP_MINUS,
        MEP_TIMES,
        MEP_DIVIDE
    };
    binary_functions_probabilites.reserve(binary_functions.size());
    segment = 1.0 / binary_functions.size();
    for (int i = 0; i < binary_functions.size() - 1; i++) {
        binary_functions_probabilites.push_back(segment * (i + 1));
    }
    binary_functions_probabilites.push_back(1);

    this->ternary_functions = {
        MEP_CONSTANT,
        MEP_PARAM,
        MEP_UNARY_MINUS,
        MEP_SQUARE,
        MEP_ROOT,
        MEP_PLUS,
        MEP_MINUS,
        MEP_TIMES,
        MEP_DIVIDE,
        MEP_BRANCH
    };
    ternary_functions_probabilites.reserve(ternary_functions.size());
    segment = 1.0 / ternary_functions.size();
    for (int i = 0; i < ternary_functions.size() - 1; i++) {
        ternary_functions_probabilites.push_back(segment * (i + 1));
    }
    ternary_functions_probabilites.push_back(1);
}

double MultiExpressionProgrammingGenotypeBlueprint::generateConstant() {
    return constant_generator->generate();
}

std::string MultiExpressionProgrammingGenotypeBlueprint::generateParam(std::vector<std::string> params) {
    return params[generator->generate() % params.size()];
}

int MultiExpressionProgrammingGenotypeBlueprint::generateArgument(int instruction_index) {
    return generator->generate() % instruction_index;
}

MEPInstructionType MultiExpressionProgrammingGenotypeBlueprint::generateNullaryFunction() {
    auto random_number = instruction_type_generator->generate();
    int i = 0;
    while (nullary_functions_probabilites[i] < random_number) {
        i++;
    }
    return nullary_functions[i];
}

MEPInstructionType MultiExpressionProgrammingGenotypeBlueprint::generateUnaryFunction() {
    auto random_number = instruction_type_generator->generate();
    int i = 0;
    while (unary_functions_probabilites[i] < random_number) {
        i++;
    }
    return unary_functions[i];
}

MEPInstructionType MultiExpressionProgrammingGenotypeBlueprint::generateBinaryFunction() {
    auto random_number = instruction_type_generator->generate();
    int i = 0;
    while (binary_functions_probabilites[i] < random_number) {
        i++;
    }
    return binary_functions[i];
}

MEPInstructionType MultiExpressionProgrammingGenotypeBlueprint::generateTernaryFunction() {
    auto random_number = instruction_type_generator->generate();
    int i = 0;
    while (ternary_functions_probabilites[i] < random_number) {
        i++;
    }
    return ternary_functions[i];
}
