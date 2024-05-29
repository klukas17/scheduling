//
// Created by mihael on 5/27/24.
//

#ifndef LGPPROGRAM_H
#define LGPPROGRAM_H
#include <string>
#include <vector>

#include "LGPInstruction.h"
#include "LGPRegistersState.h"


class LGPProgram {
public:
    std::vector<LGPInstruction*> instructions;
    std::map<int, double> load_constant_map;
    std::map<int, std::string> load_param_map;
    explicit LGPProgram(std::vector<LGPInstruction*> instructions, std::map<int, double> load_constant_map, std::map<int, std::string> load_param_map);
    ~LGPProgram();
    LGPProgram* copy();
    void executeProgram(LGPRegistersState* registers_state, std::map<std::string, double> params);
};



#endif //LGPPROGRAM_H
