//
// Created by mihael on 5/27/24.
//

#ifndef LGPREGISTERINITIALIZATIONSTRATEGYSINGULARLOADING_H
#define LGPREGISTERINITIALIZATIONSTRATEGYSINGULARLOADING_H
#include "LGPRegisterInitializationStrategy.h"


class LGPRegisterInitializationStrategySingularLoading final : public LGPRegisterInitializationStrategy {
public:
    LGPRegisterInitializationStrategySingularLoading();
    ~LGPRegisterInitializationStrategySingularLoading() override;
    void initializeRegisters(LGPRegistersState* registers_state, std::vector<std::string> inputs, std::map<std::string, double> params) override;
};



#endif //LGPREGISTERINITIALIZATIONSTRATEGYSINGULARLOADING_H
