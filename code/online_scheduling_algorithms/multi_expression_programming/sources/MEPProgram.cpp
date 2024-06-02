//
// Created by mihael on 5/30/24.
//

#include "MEPProgram.h"
#include <cmath>
#include <utility>

MEPProgram::MEPProgram(std::vector<MEPInstruction*> instructions, std::map<int, double> constant_map, std::map<int, std::string> param_map) {
    this->instructions = std::move(instructions);
    this->constant_map = std::move(constant_map);
    this->param_map = std::move(param_map);
}

MEPProgram::~MEPProgram() {
    for (auto & instruction : instructions) {
        delete instruction;
    }
}

MEPProgram* MEPProgram::copy() {
    std::vector<MEPInstruction*> new_instructions;
    new_instructions.reserve(instructions.size());
    for (auto instruction : instructions) {
        new_instructions.push_back(instruction->copy());
    }
    return new MEPProgram(new_instructions, constant_map, param_map);
}

double MEPProgram::executeProgram(std::map<std::string, double> params) {

    std::vector<double> results;
    results.reserve(instructions.size());

    for (auto instruction : instructions) {

        switch(instruction->instruction_type) {

        case MEP_PARAM:
            {
                results.push_back(params[param_map[instruction->instruction_id]]);
                break;
            }

        case MEP_CONSTANT:
            {
                results.push_back(constant_map[instruction->instruction_id]);
                break;
            }

        case MEP_UNARY_MINUS:
            {
                auto arg = results[instruction->first_param];
                results.push_back(-arg);
                break;
            }

        case MEP_PLUS:
            {
                auto arg1 = results[instruction->first_param];
                auto arg2 = results[instruction->second_param];
                results.push_back(arg1 + arg2);
                break;
            }

        case MEP_MINUS:
            {
                auto arg1 = results[instruction->first_param];
                auto arg2 = results[instruction->second_param];
                results.push_back(arg1 - arg2);
                break;
            }

        case MEP_TIMES:
            {
                auto arg1 = results[instruction->first_param];
                auto arg2 = results[instruction->second_param];
                auto res = arg1 * arg2;
                results.push_back(std::isinf(res) ? 1 : res);
                break;
            }

        case MEP_DIVIDE:
            {
                auto arg1 = results[instruction->first_param];
                auto arg2 = results[instruction->second_param];
                if (std::abs(arg2) <= 1e-6) {
                    results.push_back(1);
                } else {
                    auto res = arg1 / arg2;
                    results.push_back(std::isinf(res) ? 1 : res);
                }
                break;
            }

        case MEP_SQUARE:
            {
                auto arg = results[instruction->first_param];
                auto res = std::pow(arg, 2);
                results.push_back(std::isinf(res) ? 1 : res);
                break;
            }

        case MEP_ROOT:
            {
                auto arg = results[instruction->first_param];
                results.push_back(std::sqrt(std::abs(arg)));
                break;
            }

        case MEP_BRANCH:
            {
                auto arg1 = results[instruction->first_param];
                auto arg2 = results[instruction->second_param];
                auto arg3 = results[instruction->third_param];
                results.push_back(arg1 >= 0 ? arg2 : arg3);
                break;
            }
        }
    }

    return results.back();
}
