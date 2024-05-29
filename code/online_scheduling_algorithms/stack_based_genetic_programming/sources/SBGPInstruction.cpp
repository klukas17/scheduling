//
// Created by mihael on 5/29/24.
//

#include "SBGPInstruction.h"

SBGPInstruction::SBGPInstruction(SBGPInstructionType instruction_type, int instruction_id) {
    this->instruction_type = instruction_type;
    this->instruction_id = instruction_id;
}

SBGPInstruction* SBGPInstruction::copy() {
    return new SBGPInstruction(instruction_type, instruction_id);
}
