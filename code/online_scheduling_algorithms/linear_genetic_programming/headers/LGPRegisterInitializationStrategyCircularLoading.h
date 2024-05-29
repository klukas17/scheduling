//
// Created by mihael on 5/27/24.
//

#ifndef LGPREGISTERINITIALIZATIONSTRATEGYCIRCULARLOADING_H
#define LGPREGISTERINITIALIZATIONSTRATEGYCIRCULARLOADING_H
#include "LGPRegisterInitializationStrategy.h"


class LGPRegisterInitializationStrategyCircularLoading final : public LGPRegisterInitializationStrategy {
public:
    LGPRegisterInitializationStrategyCircularLoading();
    ~LGPRegisterInitializationStrategyCircularLoading() override;
    void initializeRegisters(LGPRegistersState* registers_state, std::vector<std::string> inputs, std::map<std::string, double> params) override;
};



#endif //LGPREGISTERINITIALIZATIONSTRATEGYCIRCULARLOADING_H
