//
// Created by mihael on 5/18/24.
//

#include "MachineBreakdownsGeneratorParameters.h"

MachineBreakdownsGeneratorParameters::MachineBreakdownsGeneratorParameters(
    long machine_id,
    long number_of_breakdowns,
    DoubleGenerator* breakdown_start_generator,
    DoubleGenerator* breakdown_duration_generator
) {
    this->machine_id = machine_id;
    this->number_of_breakdowns = number_of_breakdowns;
    this->breakdown_start_generator = breakdown_start_generator;
    this->breakdown_duration_generator = breakdown_duration_generator;
}

long MachineBreakdownsGeneratorParameters::getMachineId() const {
    return machine_id;
}

long MachineBreakdownsGeneratorParameters::getNumberOfBreakdowns() const {
    return number_of_breakdowns;
}

double MachineBreakdownsGeneratorParameters::generateBreakdownStart() const {
    return breakdown_start_generator->generate();
}

double MachineBreakdownsGeneratorParameters::generateBreakdownDuration() const {
    return breakdown_duration_generator->generate();
}
