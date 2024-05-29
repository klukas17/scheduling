//
// Created by mihael on 5/29/24.
//

#ifndef SBGPPROGRAM_H
#define SBGPPROGRAM_H
#include <map>
#include <string>
#include <vector>

#include "SBGPInstruction.h"


class SBGPProgram {
public:
    std::vector<SBGPInstruction*> instructions;
    std::map<int, double> push_constant_map;
    std::map<int, std::string> push_param_map;
    SBGPProgram(std::vector<SBGPInstruction*> instructions, std::map<int, double> push_constant_map, std::map<int, std::string> push_param_map);
    ~SBGPProgram();
    SBGPProgram* copy();
    double executeProgram(std::map<std::string, double> params);
};



#endif //SBGPPROGRAM_H
