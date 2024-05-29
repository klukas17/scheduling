//
// Created by mihael on 5/27/24.
//

#include "LGPRegisterInitializationStrategyEmptyLoading.h"

LGPRegisterInitializationStrategyEmptyLoading::LGPRegisterInitializationStrategyEmptyLoading() = default;

LGPRegisterInitializationStrategyEmptyLoading::~LGPRegisterInitializationStrategyEmptyLoading() = default;

void LGPRegisterInitializationStrategyEmptyLoading::initializeRegisters(
    LGPRegistersState* registers_state,
    std::vector<std::string> inputs,
    std::map<std::string, double> params
) {
    for (int i = 0; i < registers_state->getNumberOfRegisters(); i++) {
        registers_state->setValue(i, 0);
    }
}
