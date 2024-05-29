//
// Created by mihael on 5/27/24.
//

#include "LGPInstruction.h"

LGPInstruction::LGPInstruction(LGPInstructionType instruction_type, int first_register_id, int second_register_id, int third_register_id, int instruction_id) {
    this->instruction_type = instruction_type;
    this->first_register_id = first_register_id;
    this->second_register_id = second_register_id;
    this->third_register_id = third_register_id;
    this->instruction_id = instruction_id;
}

LGPInstruction* LGPInstruction::copy() {
    return new LGPInstruction(instruction_type, first_register_id, second_register_id, third_register_id, instruction_id);
}
