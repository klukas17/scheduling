//
// Created by mihael on 07/05/23.
//

#include "JobProcessingStep.h"

JobProcessingStep::JobProcessingStep(long processing_step_id, long machine_id) {
    this->processing_step_id = processing_step_id;
    this->machine_id = machine_id;
}

long JobProcessingStep::getProcessingStepId() const {
    return processing_step_id;
}

long JobProcessingStep::getMachineId() const {
    return machine_id;
}