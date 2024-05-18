//
// Created by mihael on 5/18/24.
//

#ifndef BREAKDOWNSGENERATORPARAMETERS_H
#define BREAKDOWNSGENERATORPARAMETERS_H
#include "DoubleGenerator.h"


class MachineBreakdownsGeneratorParameters {
    long machine_id;
    long number_of_breakdowns;
    DoubleGenerator* breakdown_start_generator;
    DoubleGenerator* breakdown_duration_generator;
public:
    MachineBreakdownsGeneratorParameters(
        long machine_id,
        long number_of_breakdowns,
        DoubleGenerator* breakdown_start_generator,
        DoubleGenerator* breakdown_duration_generator
    );
    [[nodiscard]] long getMachineId() const;
    [[nodiscard]] long getNumberOfBreakdowns() const;
    [[nodiscard]] double generateBreakdownStart() const;
    [[nodiscard]] double generateBreakdownDuration() const;
};



#endif //BREAKDOWNSGENERATORPARAMETERS_H
