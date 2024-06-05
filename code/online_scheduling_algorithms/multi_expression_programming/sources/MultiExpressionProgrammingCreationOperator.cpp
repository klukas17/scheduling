//
// Created by mihael on 5/30/24.
//

#include "MultiExpressionProgrammingCreationOperator.h"

#include <map>

#include "GEPProgram.h"
#include "MEPInstruction.h"
#include "MEPProgram.h"
#include "MultiExpressionProgramming.h"

MultiExpressionProgrammingCreationOperator::MultiExpressionProgrammingCreationOperator(GenotypeBlueprint* genotype_blueprint) : CreationOperator(genotype_blueprint) {
    this->blueprint = dynamic_cast<MultiExpressionProgrammingGenotypeBlueprint*>(genotype_blueprint);
}

MultiExpressionProgrammingCreationOperator::~MultiExpressionProgrammingCreationOperator() = default;

Genotype* MultiExpressionProgrammingCreationOperator::create() {
    std::vector<MEPInstruction*> instructions;
    instructions.reserve(blueprint->number_of_instructions);
    std::map<int, double> constant_map;
    std::map<int, std::string> param_map;

    for (int i = 0; i < blueprint->number_of_instructions; i++) {

        switch(i) {

        case 0:
            {
                auto instruction_type = blueprint->generateNullaryFunction();
                if (instruction_type == MEP_CONSTANT) {
                    constant_map[i] = blueprint->generateConstant();
                }
                if (instruction_type == MEP_PARAM) {
                    param_map[i] = blueprint->generateParam(blueprint->getInputs());
                }
                instructions.push_back(new MEPInstruction(
                    i,
                    instruction_type,
                    -1,
                    -1,
                    -1
                ));
                break;
            }

        case 1:
            {
                auto instruction_type = blueprint->generateUnaryFunction();
                if (instruction_type == MEP_CONSTANT) {
                    constant_map[i] = blueprint->generateConstant();
                }
                if (instruction_type == MEP_PARAM) {
                    param_map[i] = blueprint->generateParam(blueprint->getInputs());
                }
                instructions.push_back(new MEPInstruction(
                    i,
                    instruction_type,
                    blueprint->generateArgument(i),
                    -1,
                    -1
                ));
                break;
            }

        case 2:
            {
                auto instruction_type = blueprint->generateBinaryFunction();
                if (instruction_type == MEP_CONSTANT) {
                    constant_map[i] = blueprint->generateConstant();
                }
                if (instruction_type == MEP_PARAM) {
                    param_map[i] = blueprint->generateParam(blueprint->getInputs());
                }
                instructions.push_back(new MEPInstruction(
                    i,
                    instruction_type,
                    blueprint->generateArgument(i),
                    blueprint->generateArgument(i),
                    -1
                ));
                break;
            }

        default:
            {
                auto instruction_type = blueprint->generateTernaryFunction();
                if (instruction_type == MEP_CONSTANT) {
                    constant_map[i] = blueprint->generateConstant();
                }
                if (instruction_type == MEP_PARAM) {
                    param_map[i] = blueprint->generateParam(blueprint->getInputs());
                }
                instructions.push_back(new MEPInstruction(
                    i,
                    instruction_type,
                    blueprint->generateArgument(i),
                    blueprint->generateArgument(i),
                    blueprint->generateArgument(i)
                ));
                break;
            }
        }
    }

    auto program = new MEPProgram(instructions, constant_map, param_map);
    auto mep = new MultiExpressionProgramming(program);
    mep->setInputs(blueprint->getInputs());
    return mep;
}
