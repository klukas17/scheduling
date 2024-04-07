//
// Created by mihael on 2/11/24.
//

#ifndef MAKESPANOBJECTIVEFUNCTION_H
#define MAKESPANOBJECTIVEFUNCTION_H
#include "ObjectiveFunction.h"

class MakespanObjectiveFunction final : public ObjectiveFunction {
public:
    MakespanObjectiveFunction();
    double evaluate(SimulatorStatistics* statistics) override;
};


#endif //MAKESPANOBJECTIVEFUNCTION_H
