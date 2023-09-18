//
// Created by mihael on 9/18/23.
//

/**
 * @file BreakdownEnd.cpp
 * @brief Implements the member functions of the BreakdownEnd class.
 */

#include "BreakdownEnd.h"

BreakdownEnd::BreakdownEnd(long time, long machine_id) : Event(time), MachineEvent(time, machine_id) {
    this->event_type = BREAKDOWN_END;
    this->message = "Machine " + std::to_string(machine_id) + ": Finished breakdown";
}