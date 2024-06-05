//
// Created by mihael on 5/27/24.
//

#include "LinearGeneticProgramming.h"

LinearGeneticProgramming::LinearGeneticProgramming(LGPProgram* program, LGPRegisterInitializationStrategy* register_initialization_strategy, int number_of_registers) {
    this->program = program;
    this->register_initialization_strategy = register_initialization_strategy;
    this->number_of_registers = number_of_registers;
}

LinearGeneticProgramming::~LinearGeneticProgramming() {
    delete program;
}

LGPProgram* LinearGeneticProgramming::getProgram() {
    return program;
}

int LinearGeneticProgramming::getNumberOfRegisters() {
    return number_of_registers;
}

LGPRegisterInitializationStrategy* LinearGeneticProgramming::getRegisterInitializationStrategy() {
    return register_initialization_strategy;
}

Genotype* LinearGeneticProgramming::copy() {
    auto copy = new LinearGeneticProgramming(program->copy(), register_initialization_strategy, number_of_registers);
    copy->setInputs(inputs);
    return copy;
}

double LinearGeneticProgramming::calculateScore(std::map<std::string, double> params) {
    auto registers_state = new LGPRegistersState(number_of_registers);
    register_initialization_strategy->initializeRegisters(registers_state, inputs, params);
    program->executeProgram(registers_state, params);
    auto res = registers_state->getValue(0);
    delete registers_state;
    return res;
}
