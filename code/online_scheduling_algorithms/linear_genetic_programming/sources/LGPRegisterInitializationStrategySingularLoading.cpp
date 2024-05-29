//
// Created by mihael on 5/27/24.
//

#include "LGPRegisterInitializationStrategySingularLoading.h"

LGPRegisterInitializationStrategySingularLoading::LGPRegisterInitializationStrategySingularLoading() = default;

LGPRegisterInitializationStrategySingularLoading::~LGPRegisterInitializationStrategySingularLoading() = default;

void LGPRegisterInitializationStrategySingularLoading::initializeRegisters(
    LGPRegistersState* registers_state,
    std::vector<std::string> inputs,
    std::map<std::string, double> params
) {
    auto number_of_registers = registers_state->getNumberOfRegisters();
    for (int i = 0; i < inputs.size(); i++) {
        if (i >= number_of_registers) {
            break;
        }
        registers_state->setValue(i, params[inputs[i]]);
    }
    for (int i = inputs.size(); i < number_of_registers; i++) {
        registers_state->setValue(i, 0);
    }
}
