//
// Created by mihael on 5/8/24.
//

#include "ConstantProgramming.h"

#include "iostream"

ConstantProgramming::ConstantProgramming(double constant) {
    this->constant = constant;
}

Genotype* ConstantProgramming::copy() {
    return new ConstantProgramming(constant);
}

double ConstantProgramming::calculateScore(std::map<std::string, double> params) {
    for (const auto& [param_name, param_value] : params) {
        std::cout << param_name << "=" << param_value << ", ";
    }
    std::cout << std::endl;
    return constant;
}

