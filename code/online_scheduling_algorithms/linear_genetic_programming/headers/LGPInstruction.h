//
// Created by mihael on 5/27/24.
//

#ifndef LGPINSTRUCTION_H
#define LGPINSTRUCTION_H
#include "LGPInstructionTypes.h"


class LGPInstruction {
public:
    LGPInstructionType instruction_type;
    int first_register_id;
    int second_register_id;
    int third_register_id;
    int instruction_id;
    LGPInstruction(LGPInstructionType instruction_type, int first_register_id, int second_register_id, int third_register_id, int instruction_id);
    LGPInstruction* copy();
};



#endif //LGPINSTRUCTION_H
