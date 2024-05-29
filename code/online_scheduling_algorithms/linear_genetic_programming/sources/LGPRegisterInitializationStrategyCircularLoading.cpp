//
// Created by mihael on 5/27/24.
//

#include "LGPRegisterInitializationStrategyCircularLoading.h"

LGPRegisterInitializationStrategyCircularLoading::LGPRegisterInitializationStrategyCircularLoading() = default;

LGPRegisterInitializationStrategyCircularLoading::~LGPRegisterInitializationStrategyCircularLoading() = default;

void LGPRegisterInitializationStrategyCircularLoading::initializeRegisters(
    LGPRegistersState* registers_state,
    std::vector<std::string> inputs,
    std::map<std::string, double> params
) {
    auto number_of_inputs = inputs.size();
    for (int i = 0; i < registers_state->getNumberOfRegisters(); i++) {
        registers_state->setValue(i, params[inputs[i % number_of_inputs]]);
    }
}
