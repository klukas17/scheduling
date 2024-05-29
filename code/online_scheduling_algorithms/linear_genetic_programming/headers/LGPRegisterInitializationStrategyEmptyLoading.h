//
// Created by mihael on 5/27/24.
//

#ifndef LGPREGISTERINITIALIZATIONSTRATEGYEMPTYLOADING_H
#define LGPREGISTERINITIALIZATIONSTRATEGYEMPTYLOADING_H
#include "LGPRegisterInitializationStrategy.h"


class LGPRegisterInitializationStrategyEmptyLoading final : public LGPRegisterInitializationStrategy {
public:
    LGPRegisterInitializationStrategyEmptyLoading();
    ~LGPRegisterInitializationStrategyEmptyLoading() override;
    void initializeRegisters(LGPRegistersState* registers_state, std::vector<std::string> inputs, std::map<std::string, double> params) override;
};



#endif //LGPREGISTERINITIALIZATIONSTRATEGYEMPTYLOADING_H
