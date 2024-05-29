//
// Created by mihael on 5/27/24.
//

#include "LGPProgram.h"

#include <utility>
#include <cmath>

LGPProgram::LGPProgram(std::vector<LGPInstruction*> instructions, std::map<int, double> load_constant_map, std::map<int, std::string> load_param_map) {
    this->instructions = std::move(instructions);
    this->load_constant_map = std::move(load_constant_map);
    this->load_param_map = std::move(load_param_map);
}

LGPProgram::~LGPProgram() {
    for (auto & instruction : instructions) {
        delete instruction;
    }
}

LGPProgram* LGPProgram::copy() {
    std::vector<LGPInstruction*> new_instructions;
    new_instructions.reserve(instructions.size());
    for (auto instruction : instructions) {
        new_instructions.push_back(instruction->copy());
    }
    return new LGPProgram(new_instructions, load_constant_map, load_param_map);
}

void LGPProgram::executeProgram(LGPRegistersState* registers_state, std::map<std::string, double> params) {

    int i = 0;
    while (i < instructions.size()) {
        auto instruction = instructions[i];

        switch(instruction->instruction_type)
        {

        case LGP_LOAD_PARAM:
            {
                registers_state->setValue(
                   instruction->first_register_id,
                   params[load_param_map[instruction->instruction_id]]
               );
                break;
            }

        case LGP_LOAD_CONSTANT:
            {
                registers_state->setValue(
                   instruction->first_register_id,
                   load_constant_map[instruction->instruction_id]
               );
                break;
            }

        case LGP_UNARY_MINUS:
            {
                registers_state->setValue(
                   instruction->first_register_id,
                   -registers_state->getValue(instruction->second_register_id)
               );
                break;
            }

        case LGP_PLUS:
            {
                registers_state->setValue(
                   instruction->first_register_id,
                   registers_state->getValue(instruction->second_register_id) + registers_state->getValue(instruction->third_register_id)
               );
                break;
            }

        case LGP_MINUS:
            {
                registers_state->setValue(
                   instruction->first_register_id,
                   registers_state->getValue(instruction->second_register_id) - registers_state->getValue(instruction->third_register_id)
               );
                break;
            }

        case LGP_TIMES:
            {
                auto result = registers_state->getValue(instruction->second_register_id) * registers_state->getValue(instruction->third_register_id);
                registers_state->setValue(
                   instruction->first_register_id,
                   std::isinf(result) ? 1 : result
               );
                break;
            }

        case LGP_DIVIDE:
            {
                auto divisor = registers_state->getValue(instruction->third_register_id);
                registers_state->setValue(
                    instruction->first_register_id,
                    divisor >= -1e-6 && divisor <= 1e-6 ? 1 : registers_state->getValue(instruction->second_register_id) / divisor
                );
                break;
            }

        case LGP_SQUARE:
            {
                auto result = std::pow(registers_state->getValue(instruction->second_register_id), 2);
                registers_state->setValue(
                   instruction->first_register_id,
                   std::isinf(result) ? 1 : result
               );
                break;
            }

        case LGP_ROOT:
            {
                registers_state->setValue(
                   instruction->first_register_id,
                   std::sqrt(std::abs(registers_state->getValue(instruction->second_register_id)))
               );
                break;
            }

        case LGP_CONDITION:
            {
                if (std::abs(registers_state->getValue(instruction->first_register_id)) < 1) {
                    i++;
                }
                break;
            }

        case LGP_NOP:
            {
                break;
            }
        }

        i++;
    }
}

