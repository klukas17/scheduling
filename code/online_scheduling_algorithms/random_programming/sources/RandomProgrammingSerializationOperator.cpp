//
// Created by mihael on 5/20/24.
//

#include "RandomProgrammingSerializationOperator.h"
#include "RandomProgramming.h"
#include "sstream"

RandomProgrammingSerializationOperator::RandomProgrammingSerializationOperator() = default;

std::vector<std::string> RandomProgrammingSerializationOperator::serialize(Genotype* genotype) {
    auto random_programming = dynamic_cast<RandomProgramming*>(genotype);
    auto lower = random_programming->getLower();
    auto upper = random_programming->getUpper();
    std::ostringstream oss;
    oss << lower << " " << upper;
    return {oss.str()};
}

Genotype* RandomProgrammingSerializationOperator::deserialize(std::vector<std::string> representation) {
    std::istringstream iss(representation[0]);
    double lower, upper;
    iss >> lower >> upper;
    return new RandomProgramming(lower, upper);
}

