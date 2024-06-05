//
// Created by mihael on 5/29/24.
//

#include "SBGPProgram.h"
#include <cmath>
#include <stack>
#include <utility>

SBGPProgram::SBGPProgram(std::vector<SBGPInstruction*> instructions, std::map<int, double> push_constant_map, std::map<int, std::string> push_param_map) {
    this->instructions = std::move(instructions);
    this->push_constant_map = std::move(push_constant_map);
    this->push_param_map = std::move(push_param_map);
}

SBGPProgram::~SBGPProgram() {
    for (auto & instruction : instructions) {
        delete instruction;
    }
}

SBGPProgram* SBGPProgram::copy() {
    std::vector<SBGPInstruction*> new_instructions;
    new_instructions.reserve(instructions.size());
    for (auto instruction : instructions) {
        new_instructions.push_back(instruction->copy());
    }
    return new SBGPProgram(new_instructions, push_constant_map, push_param_map);
}

double SBGPProgram::executeProgram(std::map<std::string, double> params) {
    std::stack<double> stack;

    for (auto instruction : instructions) {

        switch(instruction->instruction_type) {

        case SBGP_PUSH_PARAM:
            {
                stack.push(params[push_param_map[instruction->instruction_id]]);
                break;
            }

        case SBGP_PUSH_CONSTANT:
            {
                stack.push(push_constant_map[instruction->instruction_id]);
                break;
            }

        case SBGP_UNARY_MINUS:
            {
                if (stack.size() < 1) break;
                auto a = stack.top();
                stack.pop(),
                stack.push(-a);
                break;
            }

        case SBGP_PLUS:
            {
                if (stack.size() < 2) break;
                auto b = stack.top();
                stack.pop();
                auto a = stack.top();
                stack.pop();
                stack.push(a + b);
                break;
            }

        case SBGP_MINUS:
            {
                if (stack.size() < 2) break;
                auto b = stack.top();
                stack.pop();
                auto a = stack.top();
                stack.pop();
                stack.push(a - b);
                break;
            }

        case SBGP_TIMES:
            {
                if (stack.size() < 2) break;
                auto b = stack.top();
                stack.pop();
                auto a = stack.top();
                stack.pop();
                auto result = a * b;
                stack.push(std::isinf(result) ? 1 : result);
                break;
            }

        case SBGP_DIVIDE:
            {
                if (stack.size() < 2) break;
                auto b = stack.top();
                stack.pop();
                auto a = stack.top();
                stack.pop();
                stack.push(b >= -1e-6 && b <= 1e-6 ? 1 : a / b);
                break;
            }

        case SBGP_SQUARE:
            {
                if (stack.size() < 1) break;
                auto a = stack.top();
                stack.pop();
                auto result = std::pow(a, 2);
                stack.push(std::isinf(result) ? 1 : result);
                break;
            }

        case SBGP_ROOT:
            {
                if (stack.size() < 1) break;
                auto a = stack.top();
                stack.pop(),
                stack.push((a >= 0 ? 1 : -1) * std::sqrt(std::abs(a)));
                break;
            }

        case SBGP_BRANCH:
            {
                if (stack.size() < 3) break;
                auto c = stack.top();
                stack.pop();
                auto b = stack.top();
                stack.pop();
                auto a = stack.top();
                stack.pop();
                stack.push(a >= 0 ? b : c);
                break;
            }

        case SBGP_NOP:
            {
                break;
            }
        }
    }

    return !stack.empty() ? stack.top() : 0;
}
