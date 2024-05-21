//
// Created by mihael on 5/8/24.
//

#include "ConstantProgramming.h"

#include "iostream"

ConstantProgramming::ConstantProgramming(double constant) {
    this->constant = constant;
}

ConstantProgramming::~ConstantProgramming() = default;

double ConstantProgramming::getConstant() {
    return constant;
}

Genotype* ConstantProgramming::copy() {
    return new ConstantProgramming(constant);
}

double ConstantProgramming::calculateScore(std::map<std::string, double> params) {
    return constant;
}

