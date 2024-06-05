//
// Created by mihael on 5/30/24.
//

#ifndef MULTIEXPRESSIONPROGRAMMINGGENOTYPEBLUEPRINT_H
#define MULTIEXPRESSIONPROGRAMMINGGENOTYPEBLUEPRINT_H
#include "DoubleGenerator.h"
#include "IntegerGenerator.h"
#include "MEPInstructionTypes.h"
#include "OnlineSchedulingAlgorithmGenotypeBlueprint.h"


class MultiExpressionProgrammingGenotypeBlueprint final : public OnlineSchedulingAlgorithmGenotypeBlueprint {
public:
    int number_of_instructions;
    DoubleGenerator* constant_generator;
    DoubleGenerator* instruction_type_generator;
    IntegerGenerator* generator;
    std::vector<MEPInstructionType> nullary_functions;
    std::vector<double> nullary_functions_probabilites;
    std::vector<MEPInstructionType> unary_functions;
    std::vector<double> unary_functions_probabilites;
    std::vector<MEPInstructionType> binary_functions;
    std::vector<double> binary_functions_probabilites;
    std::vector<MEPInstructionType> ternary_functions;
    std::vector<double> ternary_functions_probabilites;
    MultiExpressionProgrammingGenotypeBlueprint(
        int number_of_instructions,
        double constant_min,
        double constant_max
    );
    ~MultiExpressionProgrammingGenotypeBlueprint() override;
    double generateConstant();
    std::string generateParam(std::vector<std::string> params);
    int generateArgument(int instruction_index);
    MEPInstructionType generateNullaryFunction();
    MEPInstructionType generateUnaryFunction();
    MEPInstructionType generateBinaryFunction();
    MEPInstructionType generateTernaryFunction();
};



#endif //MULTIEXPRESSIONPROGRAMMINGGENOTYPEBLUEPRINT_H
