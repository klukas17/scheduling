//
// Created by mihael on 5/27/24.
//

#ifndef LGPREGISTERINITIALIZATIONSTRATEGY_H
#define LGPREGISTERINITIALIZATIONSTRATEGY_H
#include <map>
#include <string>
#include <vector>

#include "LGPRegistersState.h"


class LGPRegisterInitializationStrategy {
public:
    LGPRegisterInitializationStrategy();
    virtual ~LGPRegisterInitializationStrategy() = 0;
    virtual void initializeRegisters(LGPRegistersState* registers_state, std::vector<std::string> inputs, std::map<std::string, double> params) = 0;
};



#endif //LGPREGISTERINITIALIZATIONSTRATEGY_H
