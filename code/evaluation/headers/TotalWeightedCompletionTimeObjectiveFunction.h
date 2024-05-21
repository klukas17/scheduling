//
// Created by mihael on 5/20/24.
//

#ifndef TOTALWEIGHTEDCOMPLETIONTIMEOBJECTIVEFUNCTION_H
#define TOTALWEIGHTEDCOMPLETIONTIMEOBJECTIVEFUNCTION_H
#include "ObjectiveFunction.h"


class TotalWeightedCompletionTimeObjectiveFunction final : public ObjectiveFunction {
public:
    TotalWeightedCompletionTimeObjectiveFunction();
    double evaluate(SimulatorStatistics* statistics) override;
};



#endif //TOTALWEIGHTEDCOMPLETIONTIMEOBJECTIVEFUNCTION_H
