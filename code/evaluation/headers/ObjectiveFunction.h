//
// Created by mihael on 2/11/24.
//

#ifndef OBJECTIVEFUNCTION_H
#define OBJECTIVEFUNCTION_H
#include "SimulatorStatistics.h"


class ObjectiveFunction {
public:
    virtual double evaluate(SimulatorStatistics* statistics) = 0;
    virtual ~ObjectiveFunction();
};


#endif //OBJECTIVEFUNCTION_H
