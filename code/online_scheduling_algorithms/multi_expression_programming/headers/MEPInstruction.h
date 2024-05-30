//
// Created by mihael on 5/30/24.
//

#ifndef MEPINSTRUCTION_H
#define MEPINSTRUCTION_H

#include "MEPInstructionTypes.h"


class MEPInstruction {
public:
    int instruction_id;
    MEPInstructionType instruction_type;
    int first_param;
    int second_param;
    int third_param;
    MEPInstruction(int instruction_id, MEPInstructionType instruction_type, int first_param, int second_param, int third_param);
    MEPInstruction* copy();
};



#endif //MEPINSTRUCTION_H
