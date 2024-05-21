//
// Created by mihael on 5/20/24.
//

#include "ConstantProgrammingSerializationOperator.h"
#include "ConstantProgramming.h"
#include "sstream"

ConstantProgrammingSerializationOperator::ConstantProgrammingSerializationOperator() = default;

std::vector<std::string> ConstantProgrammingSerializationOperator::serialize(Genotype* genotype) {
    auto constant_programming = dynamic_cast<ConstantProgramming*>(genotype);
    auto constant = constant_programming->getConstant();
    std::ostringstream oss;
    oss << constant;
    return {oss.str()};
}

Genotype* ConstantProgrammingSerializationOperator::deserialize(std::vector<std::string> representation) {
    std::istringstream iss(representation[0]);
    double constant;
    iss >> constant;
    return new ConstantProgramming(constant);
}


