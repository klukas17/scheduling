//
// Created by mihael on 5/22/24.
//

#ifndef DISCOUNTEDTOTALWEIGHTEDCOMPLETIONTIMEOBJECTIVEFUNCTION_H
#define DISCOUNTEDTOTALWEIGHTEDCOMPLETIONTIMEOBJECTIVEFUNCTION_H
#include "ObjectiveFunction.h"


class DiscountedTotalWeightedCompletionTimeObjectiveFunction final : public ObjectiveFunction {
public:
    DiscountedTotalWeightedCompletionTimeObjectiveFunction();
    double evaluate(SimulatorStatistics* statistics) override;
};



#endif //DISCOUNTEDTOTALWEIGHTEDCOMPLETIONTIMEOBJECTIVEFUNCTION_H
