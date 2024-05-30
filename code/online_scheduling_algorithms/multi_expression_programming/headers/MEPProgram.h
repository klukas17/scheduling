//
// Created by mihael on 5/30/24.
//

#ifndef MEPPROGRAM_H
#define MEPPROGRAM_H
#include <map>
#include <string>
#include <vector>

#include "MEPInstruction.h"


class MEPProgram {
public:
    std::vector<MEPInstruction*> instructions;
    std::map<int, double> constant_map;
    std::map<int, std::string> param_map;
    MEPProgram(std::vector<MEPInstruction*> instructions, std::map<int, double> constant_map, std::map<int, std::string> param_map);
    ~MEPProgram();
    MEPProgram* copy();
    double executeProgram(std::map<std::string, double> params);
};



#endif //MEPPROGRAM_H
