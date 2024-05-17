//
// Created by mihael on 5/7/24.
//

#include "OnlineSchedulerStepIdGenerator.h"

OnlineSchedulerStepIdGenerator::OnlineSchedulerStepIdGenerator() {
    this->current = 0;
}

long OnlineSchedulerStepIdGenerator::generate_step_id() {
    current++;
    return current;
}
