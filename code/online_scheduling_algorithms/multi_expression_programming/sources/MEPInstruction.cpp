//
// Created by mihael on 5/30/24.
//

#include "MEPInstruction.h"

MEPInstruction::MEPInstruction(int instruction_id, MEPInstructionType instruction_type, int first_param, int second_param, int third_param) {
    this->instruction_id = instruction_id;
    this->instruction_type = instruction_type;
    this->first_param = first_param;
    this->second_param = second_param;
    this->third_param = third_param;
}

MEPInstruction* MEPInstruction::copy() {
    return new MEPInstruction(instruction_id, instruction_type, first_param, second_param, third_param);
}
