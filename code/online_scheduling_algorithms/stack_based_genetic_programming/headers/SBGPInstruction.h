//
// Created by mihael on 5/29/24.
//

#ifndef SBGPINSTRUCTION_H
#define SBGPINSTRUCTION_H
#include "SBGPInstructionTypes.h"


class SBGPInstruction {
public:
    SBGPInstructionType instruction_type;
    int instruction_id;
    SBGPInstruction(SBGPInstructionType instruction_type, int instruction_id);
    SBGPInstruction* copy();
};



#endif //SBGPINSTRUCTION_H
