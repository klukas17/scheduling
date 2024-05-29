//
// Created by mihael on 5/27/24.
//

#include "LGPRegistersState.h"

LGPRegistersState::LGPRegistersState(int number_of_registers) {
    for (int i = 0; i < number_of_registers; i++) {
        registers[i] = 0;
    }
    this->number_of_registers = number_of_registers;
}

int LGPRegistersState::getNumberOfRegisters() {
    return number_of_registers;
}

double LGPRegistersState::getValue(int register_id) {
    return registers[register_id];
}

void LGPRegistersState::setValue(int register_id, double register_value) {
    registers[register_id] = register_value;
}

